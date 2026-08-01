import SwiftUI

/// Compact status pill for a door, using a semantic color + icon and the plain
/// user-facing label (UI req. 3/5).
struct DoorStatusBadge: View {

    let status: DoorStatus

    var body: some View {
        Label {
            Text(status.localizedTitle)
        } icon: {
            Image(systemName: status.systemImage)
                .symbolRenderingMode(.hierarchical)
        }
        .font(.subheadline.weight(.medium))
        .foregroundStyle(Theme.color(for: status.tint))
        .accessibilityElement(children: .combine)
        .accessibilityLabel(status.localizedTitle)
    }
}

#Preview {
    VStack(alignment: .leading, spacing: 12) {
        DoorStatusBadge(status: .ready)
        DoorStatusBadge(status: .connecting)
        DoorStatusBadge(status: .opened)
        DoorStatusBadge(status: .unavailable)
        DoorStatusBadge(status: .noAccess)
    }
    .padding()
}
