import SwiftUI

struct HomeView: View {

    @EnvironmentObject private var environment: AppEnvironment
    @StateObject var viewModel: HomeViewModel
    @State private var confirmSignOut = false

    var body: some View {
        NavigationStack {
            ScrollView {
                VStack(spacing: 20) {
                    SeamlessToggleCard(
                        isOn: $viewModel.isSeamlessOn,
                        statusText: viewModel.seamlessStatusText,
                        subtitle: viewModel.seamlessSubtitle,
                        isBusy: viewModel.isSeamlessBusy,
                        onChange: { viewModel.setSeamless($0) }
                    )

                    bluetoothBanner

                    doorsSection
                }
                .padding(20)
            }
            .background(Color(.systemGroupedBackground).ignoresSafeArea())
            .navigationTitle(L10n.string("home.title"))
            .refreshable { await viewModel.refreshKeys() }
            .toolbar {
                ToolbarItem(placement: .topBarTrailing) {
                    Button {
                        confirmSignOut = true
                    } label: {
                        Image(systemName: "rectangle.portrait.and.arrow.right")
                    }
                    .accessibilityLabel(L10n.string("auth.sign_out"))
                }
            }
        }
        .onAppear { viewModel.onAppear() }
        .overlay { successOverlay }
        .animation(.default, value: viewModel.doors)
        .animation(.spring(response: 0.4, dampingFraction: 0.8), value: viewModel.successDoorName)
        .alert(item: $viewModel.activeError) { error in
            Alert(
                title: Text(error.title),
                message: Text(error.message),
                primaryButton: .default(Text(error.primaryAction.title)) {
                    viewModel.perform(error.primaryAction)
                },
                secondaryButton: .cancel(Text(L10n.string("common.ok")))
            )
        }
        .confirmationDialog(
            L10n.string("auth.sign_out.confirm.title"),
            isPresented: $confirmSignOut,
            titleVisibility: .visible
        ) {
            Button(L10n.string("auth.sign_out"), role: .destructive) {
                environment.signOutCleanup()
            }
            Button(L10n.string("common.cancel"), role: .cancel) {}
        } message: {
            Text(L10n.string("auth.sign_out.confirm.message"))
        }
    }

    // MARK: Sections

    @ViewBuilder
    private var bluetoothBanner: some View {
        if let error = viewModel.bluetooth.error {
            HStack(spacing: 12) {
                Image(systemName: "exclamationmark.triangle.fill")
                    .foregroundStyle(.orange)
                    .accessibilityHidden(true)
                VStack(alignment: .leading, spacing: 2) {
                    Text(error.title).font(.subheadline.weight(.semibold))
                    Text(error.message).font(.footnote).foregroundStyle(.secondary)
                }
                Spacer(minLength: 8)
                Button(error.primaryAction.title) { viewModel.perform(error.primaryAction) }
                    .font(.subheadline.weight(.semibold))
                    .buttonStyle(.bordered)
            }
            .card()
            .accessibilityElement(children: .combine)
        }
    }

    private var doorsSection: some View {
        VStack(alignment: .leading, spacing: 12) {
            Text(L10n.string("doors.section"))
                .font(.headline)
                .foregroundStyle(.secondary)
                .frame(maxWidth: .infinity, alignment: .leading)
                .accessibilityAddTraits(.isHeader)

            if viewModel.doors.isEmpty {
                emptyState
            } else {
                ForEach(viewModel.doors) { door in
                    DoorRowView(door: door) { viewModel.open(door) }
                }
            }
        }
    }

    private var emptyState: some View {
        VStack(spacing: 8) {
            Image(systemName: "door.left.hand.closed")
                .font(.system(size: 40))
                .foregroundStyle(.secondary)
                .accessibilityHidden(true)
            Text(L10n.string("doors.empty.title")).font(.headline)
            Text(L10n.string("doors.empty.message"))
                .font(.callout)
                .foregroundStyle(.secondary)
                .multilineTextAlignment(.center)
        }
        .frame(maxWidth: .infinity)
        .padding(.vertical, 32)
        .card()
    }

    @ViewBuilder
    private var successOverlay: some View {
        if let name = viewModel.successDoorName {
            OpenSuccessOverlay(doorName: name)
                .transition(.opacity)
        }
    }
}

#Preview {
    HomeView(viewModel: HomeViewModel(environment: AppEnvironment()))
        .environmentObject(AppEnvironment())
        .environmentObject(SessionStore())
}
