declare namespace RewardsInternals {
  export interface ApplicationState {
    rewardsInternalsData: State | undefined
  }

  export interface State {
    info: {
      keyInfoSeed: string,
      walletPaymentId: string
    }
  }
}
