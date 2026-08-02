import SwiftUI

/// Shows sign-in until the resident is authenticated, then the home screen.
struct RootView: View {

    @EnvironmentObject private var environment: AppEnvironment
    @EnvironmentObject private var session: SessionStore

    var body: some View {
        Group {
            if session.isSignedIn {
                HomeView(viewModel: HomeViewModel(environment: environment))
                    .transition(.opacity)
            } else {
                LoginView(viewModel: AuthViewModel(environment: environment))
                    .transition(.opacity)
            }
        }
        .animation(.easeInOut(duration: 0.25), value: session.isSignedIn)
    }
}

#Preview {
    RootView()
        .environmentObject(AppEnvironment())
        .environmentObject(SessionStore())
}
