import SwiftUI

/// Brief celebratory overlay shown when a door opens (UI req. 7). Pairs with a
/// success haptic fired by the view model.
struct OpenSuccessOverlay: View {

    let doorName: String
    @State private var appeared = false

    var body: some View {
        ZStack {
            Color.black.opacity(appeared ? 0.25 : 0)
                .ignoresSafeArea()

            VStack(spacing: 16) {
                ZStack {
                    Circle()
                        .fill(Color.green.opacity(0.15))
                        .frame(width: 120, height: 120)
                        .scaleEffect(appeared ? 1 : 0.4)
                    Image(systemName: "lock.open.fill")
                        .font(.system(size: 52, weight: .bold))
                        .foregroundStyle(.green)
                        .scaleEffect(appeared ? 1 : 0.2)
                        .rotationEffect(.degrees(appeared ? 0 : -25))
                }

                VStack(spacing: 4) {
                    Text(L10n.string("open.success"))
                        .font(.title3.weight(.bold))
                    Text(doorName)
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }
                .opacity(appeared ? 1 : 0)
            }
            .padding(32)
            .background(
                RoundedRectangle(cornerRadius: 28, style: .continuous)
                    .fill(.ultraThinMaterial)
            )
            .scaleEffect(appeared ? 1 : 0.8)
        }
        .onAppear {
            withAnimation(.spring(response: 0.45, dampingFraction: 0.6)) {
                appeared = true
            }
        }
        .accessibilityElement(children: .combine)
        .accessibilityLabel("\(L10n.string("open.success")), \(doorName)")
        .accessibilityAddTraits(.updatesFrequently)
        .allowsHitTesting(false)
    }
}

#Preview {
    OpenSuccessOverlay(doorName: "Входная дверь")
}
