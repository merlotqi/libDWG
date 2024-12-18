
namespace dwg {
namespace Entities {

class TableEntity : public Insert
{
public:
    enum CellStyleTypeType
    {
        Cell = 1,
        Row,
        Column,
        FormattedTableData,
        Table,
    };

    enum BorderType : short
    {
        Single = 1,
        Double = 2,
    };

    enum BreakFlowDirection
    {
        Right = 1,
        Vertical,
        Left,
    };

    enum BreakOptionFlags
    {
        None,
        EnableBreaks = 1,
        RepeatTopLabels = 2,
        RepeatBottomLabels = 4,
        AllowManualPositions = 8,
        AllowManualHeights = 16,
    };

    class Row
    {
        double m_height;
        int m_customData;
    };
};

}// namespace Entities
}// namespace dwg