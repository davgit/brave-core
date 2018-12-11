/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_shields/browser/tracking_protection_helper.h"

#include "chrome/browser/ui/browser_list.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_user_data.h"
#include "ui/base/page_transition_types.h"

using content::NavigationHandle;
using content::RenderFrameHost;
using content::WebContents;

namespace brave_shields {

base::Lock TrackingProtectionHelper::frame_data_map_lock_;

std::map<TrackingProtectionHelper::RenderFrameIdKey, GURL>
    TrackingProtectionHelper::render_frame_key_to_starting_site_url;

TrackingProtectionHelper::RenderFrameIdKey::RenderFrameIdKey()
    : render_process_id(content::ChildProcessHost::kInvalidUniqueID),
      frame_routing_id(MSG_ROUTING_NONE) {}

TrackingProtectionHelper::RenderFrameIdKey::RenderFrameIdKey(
    int render_process_id,
    int frame_routing_id)
    : render_process_id(render_process_id),
      frame_routing_id(frame_routing_id) {}

bool TrackingProtectionHelper::RenderFrameIdKey::operator<(
    const RenderFrameIdKey& other) const {
  return std::tie(render_process_id, frame_routing_id) <
         std::tie(other.render_process_id, other.frame_routing_id);
}

bool TrackingProtectionHelper::RenderFrameIdKey::operator==(
    const RenderFrameIdKey& other) const {
  return render_process_id == other.render_process_id &&
         frame_routing_id == other.frame_routing_id;
}

TrackingProtectionHelper::TrackingProtectionHelper(WebContents*
  web_contents)
    : WebContentsObserver(web_contents) {
}

TrackingProtectionHelper::~TrackingProtectionHelper() {
}

void TrackingProtectionHelper::DidStartNavigation(NavigationHandle* handle) {
  base::AutoLock lock(frame_data_map_lock_);
  
  RenderFrameHost *rfh = web_contents()->GetMainFrame();

  const RenderFrameIdKey key(rfh->GetProcess()->GetID(), rfh->GetRoutingID());

  if (handle && !ui::PageTransitionIsRedirect(handle->GetPageTransition())) {
    std::map<RenderFrameIdKey, GURL>::iterator iter =
        render_frame_key_to_starting_site_url.find(key);
    if (iter != render_frame_key_to_starting_site_url.end()) {
      render_frame_key_to_starting_site_url.erase(key);
    }
    render_frame_key_to_starting_site_url.insert(
        std::pair<RenderFrameIdKey, GURL>(key, handle->GetURL()));
  }
  return;
}

void TrackingProtectionHelper::RenderFrameHostChanged(
    RenderFrameHost* old_host, RenderFrameHost* new_host) {
  base::AutoLock lock(frame_data_map_lock_);
  if (!old_host || !new_host || old_host->GetParent() ||
      new_host->GetParent()) {
    return;
  }
  const RenderFrameIdKey old_key(old_host->GetProcess()->GetID(),
    old_host->GetRoutingID());

  std::map<RenderFrameIdKey, GURL>::iterator iter =
      render_frame_key_to_starting_site_url.find(old_key);
  if (iter != render_frame_key_to_starting_site_url.end()) {
    const RenderFrameIdKey new_key(new_host->GetProcess()->GetID(),
      new_host->GetRoutingID());
    render_frame_key_to_starting_site_url.insert(
        std::pair<RenderFrameIdKey, GURL>(new_key, iter->second));
    render_frame_key_to_starting_site_url.erase(old_key);
  }
}

// static
GURL TrackingProtectionHelper::GetStartingSiteURLFromRenderFrameInfo(
    int render_process_id, int render_frame_id) {
  base::AutoLock lock(frame_data_map_lock_);
  const RenderFrameIdKey key(render_process_id, render_frame_id);
  std::map<RenderFrameIdKey, GURL>::iterator iter =
      render_frame_key_to_starting_site_url.find(key);
  if (iter != render_frame_key_to_starting_site_url.end()) {
    return iter->second;
  }
  return GURL();
}


}  // namespace brave_shields
