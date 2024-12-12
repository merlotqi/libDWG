class CadDocument : IHandledCadObject
{
public:
    unsigned long handle() const override;

    CadHeader getHeader() const;

    void setHeader(const CadHeader &value);

    CadSummaryInfo getSummaryInfo() const;

    void setSummaryInfo(const CadSummaryInfo &value);

    DxfCalssCollection getClasses() const;

    void setClasses(const DxfCalssCollection& value);

    AppIdsTable getAppIds() const;

    void setAppIds(const AppIdsTable& value);

    BlockRecordsTable getBlockRecords() const;

    void setBlockRecords(const BlockRecordsTable& value);

    DimensionStylesTable getDimensionStyles() const;

    void setDimensionStyles(const DimensionStylesTable& value);

    LayersTable getLayers() const;

    void setLayers(const LayersTable& value);

    LineTypesTable getLineTypes() const;

    void setLineTypes(const LineTypesTable &value);

    TextStylesTable getTextStyles() const;

    void setTextStyles(const TextStylesTable &value);

    UCSTable getUCSs() const;

    void setUCSs(const UCSTable & value);

    ViewsTable getViews() const;

    void setViews(const ViewsTable &value);

    VPortsTable getVPorts() const;

    void setVPorts(const VPortsTable &value);

    LayoutCollection getLayouts() const;

    void setLayouts(const LayoutCollection &value);

    GroupCollection getGroups() const;

    void setGroups(const GroupCollection &value);

    

};