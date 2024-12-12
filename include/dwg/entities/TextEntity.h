
namespace dwg {
namespace Entities {

enum TextHorizontalAlignment : short {
    Left = 0,
    Center = 1,
    Right = 2,
    /// <summary>
    /// Aligned (if vertical alignment = 0)
    /// </summary>
    Aligned = 3,
    /// <summary>
    /// Middle (if vertical alignment = 0)
    /// </summary>
    Middle = 4,
    /// <summary>
    /// Fit (if vertical alignment = 0)
    /// </summary>
    Fit = 5,
};

enum TextMirrorFlag : short
	{
		None = 0,
		/// <summary>
		/// Mirrored in X
		/// </summary>
		Backward = 2,

		/// <summary>
		/// Mirrored in Y
		/// </summary>
		UpsideDown = 4,
	}

	enum TextVerticalAlignmentType : short
	{
		/// <summary>
		/// Text aligned to baseline.
		/// </summary>
		Baseline = 0,

		/// <summary>
		/// Bottom
		/// </summary>
		Bottom = 1,

		/// <summary>
		/// Middle
		/// </summary>
		Middle = 2,

		/// <summary>
		/// Top
		/// </summary>
		Top = 3,
	}

} // namespace Entities
} // namespace dwg