import SwiftUI

struct LoginView: View {

    @StateObject var viewModel: AuthViewModel

    var body: some View {
        NavigationStack {
            ScrollView {
                VStack(spacing: 24) {
                    header

                    VStack(spacing: 16) {
                        TextField(L10n.string("auth.email"), text: $viewModel.email)
                            .textContentType(.username)
                            .keyboardType(.emailAddress)
                            .textInputAutocapitalization(.never)
                            .autocorrectionDisabled()

                        SecureField(L10n.string("auth.password"), text: $viewModel.password)
                            .textContentType(.password)
                    }
                    .textFieldStyle(.roundedBorder)
                    .font(.body)

                    if let error = viewModel.errorMessage {
                        Text(error)
                            .font(.callout)
                            .foregroundStyle(.red)
                            .frame(maxWidth: .infinity, alignment: .leading)
                            .accessibilityAddTraits(.isStaticText)
                    }

                    Button {
                        Task { await viewModel.signIn() }
                    } label: {
                        HStack {
                            if viewModel.isSubmitting { ProgressView() }
                            Text(viewModel.isSubmitting
                                 ? L10n.string("auth.signing_in")
                                 : L10n.string("auth.sign_in"))
                                .fontWeight(.semibold)
                        }
                        .frame(maxWidth: .infinity)
                    }
                    .buttonStyle(.borderedProminent)
                    .controlSize(.large)
                    .disabled(!viewModel.canSubmit)
                }
                .padding(24)
            }
            .navigationTitle(L10n.string("auth.title"))
            .background(Color(.systemGroupedBackground).ignoresSafeArea())
        }
    }

    private var header: some View {
        VStack(spacing: 12) {
            Image(systemName: "lock.shield.fill")
                .font(.system(size: 56))
                .foregroundStyle(Color.accentColor)
                .accessibilityHidden(true)
            Text(L10n.string("auth.subtitle"))
                .font(.headline)
                .multilineTextAlignment(.center)
                .foregroundStyle(.secondary)
        }
        .padding(.top, 32)
    }
}

#Preview {
    LoginView(viewModel: AuthViewModel(environment: AppEnvironment()))
}
