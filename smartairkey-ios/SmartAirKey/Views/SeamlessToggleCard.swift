import SwiftUI

/// The large, prominent "Seamless Access" control at the top of the home screen
/// (UI req. 1): a big toggle plus the current status and a plain description.
struct SeamlessToggleCard: View {

    @Binding var isOn: Bool
    let statusText: String
    let subtitle: String
    let isBusy: Bool
    let onChange: (Bool) -> Void

    var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            HStack(alignment: .center, spacing: 16) {
                ZStack {
                    Circle()
                        .fill(isOn ? Color.accentColor.opacity(0.18) : Color(.tertiarySystemFill))
                        .frame(width: 56, height: 56)
                    Image(systemName: "dot.radiowaves.left.and.right")
                        .font(.system(size: 28, weight: .semibold))
                        .foregroundStyle(isOn ? Color.accentColor : Color.secondary)
                        .symbolRenderingMode(.hierarchical)
                }
                .accessibilityHidden(true)

                VStack(alignment: .leading, spacing: 4) {
                    Text(L10n.string("seamless.title"))
                        .font(.title3.weight(.bold))
                    HStack(spacing: 6) {
                        if isBusy { ProgressView().controlSize(.mini) }
                        Text(statusText)
                            .font(.subheadline.weight(.semibold))
                            .foregroundStyle(isOn ? Color.accentColor : .secondary)
                    }
                }

                Spacer()

                Toggle("", isOn: $isOn)
                    .labelsHidden()
                    .onChange(of: isOn) { newValue in onChange(newValue) }
                    .accessibilityLabel(L10n.string("seamless.title"))
                    .accessibilityValue(statusText)
                    .accessibilityHint(L10n.string("seamless.accessibility.hint"))
            }

            Text(subtitle)
                .font(.callout)
                .foregroundStyle(.secondary)
                .fixedSize(horizontal: false, vertical: true)
        }
        .card()
        // Group into one meaningful element order for VoiceOver.
        .accessibilityElement(children: .contain)
    }
}

#Preview {
    VStack {
        SeamlessToggleCard(isOn: .constant(true),
                           statusText: "Включено",
                           subtitle: "Двери открываются сами, когда вы подходите.",
                           isBusy: false,
                           onChange: { _ in })
        SeamlessToggleCard(isOn: .constant(false),
                           statusText: "Выключено",
                           subtitle: "Открывайте двери вручную кнопкой «Открыть».",
                           isBusy: false,
                           onChange: { _ in })
    }
    .padding()
    .background(Color(.systemGroupedBackground))
}
