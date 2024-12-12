

namespace dwg {
namespace Tables {

/// Display Ucs icon
/// </summary>
enum UscIconType : short
	{
		/// <summary>
		/// Off; No icon is displayed
		/// </summary>
		Off,

		/// <summary>
		/// On; the icon is displayed only in the lower-left corner of the current viewport or layout
		/// </summary>
		OnLower,

		/// <summary>
		/// Off; if the icon is turned on, it is displayed at the UCS origin, if possible
		/// </summary>
		OffOrigin,

		/// <summary>
		/// On; Displays the UCS icon at the origin, if possible.
		/// </summary>
		OnOrigin
	}

	/// Default lighting type

	public enum DefaultLightingType : short
	{
		/// <summary>
		/// One distant light
		/// </summary>
		OneDistantLight,
		/// <summary>
		/// Two distant lights
		/// </summary>
		TwoDistantLights,
	};

enum GridFlags : short
	{
		_0 = 0,
		_1 = 1,
		_2 = 2,
		_3 = 4,
		_4 = 8,
	}

    class VPort : public TableEntity
    {

    };

} // namespace Tables
} // namespace dwg