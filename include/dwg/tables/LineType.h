
namespace dwg {
namespace Tables {

/// Represents a line type complex element type.
enum LinetypeShapeFlags : short
	{
		/// <summary>
		/// None.
		/// </summary>
		None = 0,

		/// <summary>
		/// Text is rotated 0 degrees, otherwise it follows the segment.
		/// </summary>
		RotationIsAbsolute = 1,

		/// <summary>
		/// Complex shape code holds the index of the shape to be drawn.
		/// </summary>
		Text = 2,

		/// <summary>
		/// Complex shape code holds the index into the text area of the string to be drawn.
		/// </summary>
		Shape = 4,
	}

    class LineType : public TableEntity
    {
public:
    class Segment {};

    const char *BY_LAYER_NAME = "ByLayer";
    const char *BY_BLOCK_NAME = "ByBlock";
};

} // namespace Tables
} // namespace dwg