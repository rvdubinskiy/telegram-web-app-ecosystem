import SwiftUI

/// Colors and reusable styling. Everything is system/semantic so light & dark
/// themes and Dynamic Type work automatically (UI req. 6).
enum Theme {

    static func color(for tint: DoorStatusTint) -> Color {
        switch tint {
        case .positive: return .green
        case .neutral: return .accentColor
        case .muted: return .secondary
        case .negative: return .orange
        }
    }
}

/// Card container used across the app.
struct CardModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .padding(20)
            .frame(maxWidth: .infinity, alignment: .leading)
            .background(
                RoundedRectangle(cornerRadius: 20, style: .continuous)
                    .fill(Color(.secondarySystemGroupedBackground))
            )
    }
}

extension View {
    func card() -> some View { modifier(CardModifier()) }
}
