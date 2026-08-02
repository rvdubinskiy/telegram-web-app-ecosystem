import SwiftUI

/// A single door: its name, current status, and an "Open" action (UI req. 2).
struct DoorRowView: View {

    let door: Door
    let onOpen: () -> Void

    var body: some View {
        HStack(spacing: 16) {
            VStack(alignment: .leading, spacing: 6) {
                Text(door.name)
                    .font(.headline)
                    .foregroundStyle(.primary)
                DoorStatusBadge(status: door.status)
            }

            Spacer(minLength: 12)

            openButton
        }
        .card()
        .accessibilityElement(children: .contain)
        .accessibilityLabel("\(door.name), \(door.status.localizedTitle)")
    }

    @ViewBuilder
    private var openButton: some View {
        switch door.status {
        case .opening:
            ProgressView()
                .frame(width: 96, height: 36)
                .accessibilityLabel(L10n.string("door.opening"))
        case .opened:
            Label(L10n.string("door.opened"), systemImage: "checkmark.circle.fill")
                .labelStyle(.titleAndIcon)
                .font(.subheadline.weight(.semibold))
                .foregroundStyle(.green)
                .frame(minWidth: 96)
                .accessibilityLabel(L10n.string("door.opened"))
        default:
            Button(action: onOpen) {
                Text(L10n.string("door.open"))
                    .fontWeight(.semibold)
                    .frame(minWidth: 72)
            }
            .buttonStyle(.borderedProminent)
            .controlSize(.regular)
            .disabled(!door.status.canOpen)
            .accessibilityLabel("\(L10n.string("door.open")) — \(door.name)")
            .accessibilityHint(door.status.canOpen ? "" : door.status.localizedTitle)
        }
    }
}

#Preview {
    VStack(spacing: 16) {
        DoorRowView(door: Door(id: "1", name: "Входная дверь", status: .ready), onOpen: {})
        DoorRowView(door: Door(id: "2", name: "Подъезд", status: .connecting), onOpen: {})
        DoorRowView(door: Door(id: "3", name: "Гараж", status: .unavailable), onOpen: {})
        DoorRowView(door: Door(id: "4", name: "Офис", status: .opened), onOpen: {})
    }
    .padding()
    .background(Color(.systemGroupedBackground))
}
