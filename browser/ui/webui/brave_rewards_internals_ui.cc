/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/webui/brave_rewards_internals_ui.h"

#include "brave/components/brave_rewards/browser/rewards_service.h"
#include "brave/components/brave_rewards/browser/rewards_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/render_view_host.h"

#if !defined(OS_ANDROID)
#include "brave/components/brave_rewards/resources/grit/brave_rewards_internals_generated_map.h"
#include "brave/components/brave_rewards/resources/grit/brave_rewards_resources.h"
#else
#include "components/brave_rewards/settings/resources/grit/brave_rewards_settings_generated_map.h"
#include "components/grit/components_resources.h"
#include "components/grit/components_scaled_resources.h"
#endif

BraveRewardsInternalsUI::BraveRewardsInternalsUI(content::WebUI* web_ui,
                                                 const std::string& name)
    : BasicUI(web_ui,
              name,
#if !defined(OS_ANDROID)
              kBraveRewardsInternalsGenerated,
              kBraveRewardsInternalsGeneratedSize,
#else
              kBraveRewardsInternalsSettingsGenerated,
              kBraveRewardsInternalsSettingsGeneratedSize,
#endif
              IDR_BRAVE_REWARDS_INTERNALS_HTML) {
  Profile* profile = Profile::FromWebUI(web_ui);
  rewards_service_ =
      brave_rewards::RewardsServiceFactory::GetForProfile(profile);
}

BraveRewardsInternalsUI::~BraveRewardsInternalsUI() {
}

void BraveRewardsInternalsUI::CustomizeWebUIProperties(content::RenderViewHost* render_view_host) {
  DCHECK(IsSafeToSetWebUIProperties());

  if (render_view_host) {
    render_view_host->SetWebUIProperty("walletPaymentId",
                                       rewards_service_->GetPaymentId());
    render_view_host->SetWebUIProperty("keyInfoSeed",
                                       rewards_service_->GetKeyInfoSeed());
  }
}

void BraveRewardsInternalsUI::UpdateWebUIProperties() {
  if (IsSafeToSetWebUIProperties()) {
    CustomizeWebUIProperties(GetRenderViewHost());
  }
}
