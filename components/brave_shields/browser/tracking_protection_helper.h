/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_SHIELDS_BROWSER_TRACKING_PROTECTION_HELPER_H_
#define BRAVE_COMPONENTS_BRAVE_SHIELDS_BROWSER_TRACKING_PROTECTION_HELPER_H_

#include "base/macros.h"
#include "base/synchronization/lock.h"
#include "base/strings/string16.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
class NavigationHandle;
}

class TrackingProtectionService;

namespace brave_shields {

class TrackingProtectionHelper : public content::WebContentsObserver,
  public content::WebContentsUserData<TrackingProtectionHelper> {
  public:
    TrackingProtectionHelper(content::WebContents*);
    ~TrackingProtectionHelper() override;
    void DidStartNavigation(content::NavigationHandle* 
      navigation_handle) override;
    static GURL GetStartingSiteURLFromRenderFrameInfo(int render_process_id, 
      int render_frame_id);
    void RenderFrameHostChanged(content::RenderFrameHost* old_host,
                              content::RenderFrameHost* new_host) override;

  protected:
    struct RenderFrameIdKey {
      RenderFrameIdKey();
      RenderFrameIdKey(int render_process_id, int frame_routing_id);

    int render_process_id;
    int frame_routing_id;

    bool operator<(const RenderFrameIdKey& other) const;
    bool operator==(const RenderFrameIdKey& other) const;
  };

  static std::map<RenderFrameIdKey, GURL> render_frame_key_to_starting_site_url;
  static base::Lock frame_data_map_lock_;

  DISALLOW_COPY_AND_ASSIGN(TrackingProtectionHelper);
};

}  // namespace brave_shields

#endif  // BRAVE_COMPONENTS_BRAVE_SHIELDS_BROWSER_TRACKING_PROTECTION_HELPER_H_