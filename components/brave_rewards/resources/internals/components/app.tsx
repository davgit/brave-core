/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { connect } from 'react-redux'

// Components
import { KeyInfoSeed } from './keyInfoSeed'
import { WalletPaymentId } from './walletPaymentId'

interface Props {
  rewardsInternalsData: RewardsInternals.State
}

export class RewardsInternalsPage extends React.Component<Props, {}> {
  render () {
    const { rewardsInternalsData } = this.props
    return (
      <div id='rewardsInternalsPage'>
        <KeyInfoSeed keyInfoSeed={rewardsInternalsData.info.keyInfoSeed || ''} />
        <WalletPaymentId walletPaymentId={rewardsInternalsData.info.walletPaymentId || ''} />
      </div>)
  }
}

export const mapStateToProps = (state: RewardsInternals.ApplicationState) => ({
  rewardsInternalsData: state.rewardsInternalsData
})

export default connect(
  mapStateToProps
)(RewardsInternalsPage)
