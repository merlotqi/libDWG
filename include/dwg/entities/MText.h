namespace dwg {
namespace Entities {

enum BackgroundFillFlags : unsigned char {
    /// <summary>
    /// None
    /// </summary>
    None = 0,

    /// <summary>
    /// Use the background color
    /// </summary>
    UseBackgroundFillColor = 1,

    /// <summary>
    /// Use the drawing window color
    /// </summary>
    UseDrawingWindowColor = 2,

    /// <summary>
    /// Adds a text frame
    /// </summary>
    TextFrame = 16, // 0x10
};

class MText : public Entity, IText {
public:
    struct Edge {
        int Start;
        int End;
        double Crease;

        Edge(int start, int end);
    };
};

} // namespace Entities
} // namespace dwg