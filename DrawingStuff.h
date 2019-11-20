#pragma once
class CDrawingStuff
{
};

#ifdef NOT_COMPILE

enum SelectMode : int
{
    none,
    netselect,
    move,
    size
};

enum ElementType : int
{
    type_unknown,
    type_select,
    type_shapes_simple,
    type_image,
    type_shapes_infrastructure,
    type_text,
    type_shapes_development,
    type_shapes_import
};

#define OffsetShapes_Simple			0
#define OffsetShapes_Image			50
#define OffsetShapes_Infrastructure 100
#define OffsetShapes_Text			200
#define OffsetShapes_Development	300
#define OffsetShapes_Import			400

enum ShapeType : int
{
    // Simple
    line = OffsetShapes_Simple,
    line_right,
    rectangle,
    ellipse,
    rectangle_round,
    triangle,
    line_broken,
    line_broken_right,
    notimp_igloo,
    notimpl_multi_line,
    arrow_right,
    arrow_down,
    notimpl_courbe1,
    notimpl_courbe2,
    parenthese_left,
    parenthese_right,
    star,
    line2 = 18,
    line_right2,
    line_left_right,
    // Image
    image_fixed = OffsetShapes_Image,
    image_scaled,
    // Infrastructure
    infrastructure_server_ad = OffsetShapes_Infrastructure,
    infrastructure_server,
    infrastructure_server_web,
    infrastructure_server_database,
    infrastructure_workstation,
    infrastructure_laptop,
    infrastructure_firewall,
    infrastructure_network,
    infrastructure_virtual_server,
    infrastructure_virtual_server_web,
    infrastructure_virtual_server_database,
    infrastructure_virtualization_server,
    infrastructure_server_ad_grey,
    infrastructure_server_grey,
    infrastructure_server_database_grey,
    infrastructure_server_farm,
    infrastructure_workstation_grey,
    infrastructure_laptop_grey,
    // Text
    text = OffsetShapes_Text,
    text_left,
    text_center,
    text_right,
    text_justify,
    // Development
    development_class = OffsetShapes_Development,
    development_interface,
    development_enumeration,
    development_package,
    development_comment,
    development_component,
    development_association,
    development_aggregation,
    development_composition,
    development_dependency,
    development_inheritance,
    development_package_import,
    development_connector,
    import_class = OffsetShapes_Import,
    unknown = 1000
};

enum TrackerState
{
    normal,
    selected,
    active
};

// Hints for UpdateAllViews/OnUpdate
#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_DRAWOBJ     1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3
#define HINT_UPDATE_OLE_ITEMS   4

class CShapeType
{
public:
    static ShapeType ToShapeType(int value);
};

class CElement;
class CModeler1View;
class CElementContainer;
class CElementManager;
class CDrawingContext;

class CElement : public CObject
{
public:
    DECLARE_SERIAL(CElement);
    CElement();
    virtual ~CElement(void);

    // Internal ID is a GUID
    static int m_counter;
    void SetGuid();
    void SetName();

    // Copy an object
    std::shared_ptr<CElement> MakeCopy();

    // Virtual Operations
public:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    virtual void Draw(CModeler1View* pView, CDC* pDC);
    virtual void Draw(CDrawingContext& ctxt);

    // Operations
public:
    CString ToString();
    CString ToString(ElementType type);
    CString ToString(ShapeType type);
    //static bool IsDrawable(ElementType type);
    bool Intersects(const CRect& rect);
    void InvalidateObj(void);
    void CheckForKeepingAMinimumSize();

    // Managing/Viewing Object Selection & Tracker helpers
public:
    int GetHandleCount();
    int HitTest(CPoint point, CModeler1View* pView, bool bSelected);
    CRect GetHandleRect(int nHandleID, CModeler1View* pView);
    CPoint GetHandle(int nHandle);
    void DrawTracker(CDrawingContext& ctxt, TrackerState state);
    HCURSOR GetHandleCursor(int nHandle);
    void MoveHandleTo(int nHandle, CPoint point, CModeler1View* pView);

    // Managing Object Format
public:
    virtual bool CanChangeFillColor() const;
    virtual bool CanChangeLineColor() const;
    virtual bool CanChangeLineWidth() const;

    // Attributes
public:
    std::wstring m_name;
    ElementType m_type;
    ShapeType m_shapeType;
    std::wstring m_objectId;
    std::wstring m_caption;
    std::wstring m_text;
    std::wstring m_fontName;
    int m_fontSize;
    CRect m_rect;
    CPoint m_point;
    CPoint m_last;
    COLORREF m_colorFill;
    bool m_bColorFill;
    COLORREF m_colorLine;
    bool m_bSolidColorFill;
    bool m_bColorLine;
    int m_lineWidth;
    bool m_bLineWidth;
    std::wstring m_image;
    // Handling Moving stuff
    bool m_bMoving;
    // Connectivity
    CElementManager* m_pManager;
    CModeler1View* m_pView;

    // Methods for Attributes
public:
    bool IsLine();std::wstring GetImageFilePath();
    bool HasColorFill()	const { return m_bColorFill; }
    bool IsSolidColorFill()	const { return m_bSolidColorFill; }
    bool HasColorLine()	const { return m_bColorLine; }

    // Extra Pointer plumbing
public:
    CElementManager* GetManager() const { return m_pManager; }
    CModeler1View* GetView() const { return m_pView; }
};

class CDrawingContext
{
public:
    // Drawing Attributes are built in the ctor
    CDrawingContext(std::shared_ptr<CElement> pElement);
    virtual ~CDrawingContext(void);

public:
    Graphics* GetGraphics() { return m_pGraphics; }
    // Methods for Drawing Attributes
public:
    Color& GetColorWhite() { return m_gdiColorWhite; }
    Color& GetColorBlack() { return m_gdiColorBlack; }
    Color& GetColorLine() { return m_gdiColorLine; }
    Color& GetColorFill() { return m_gdiColorFill; }
    Pen& GetPenBlack() { return m_gdiPenBlack; }
    Pen& GetPenColor() { return m_gdiPenColor; }
    SolidBrush& GetBrushColor() { return m_gdiBrushColor; }
    SolidBrush& GetBrushBlack() { return m_gdiBrushBlack; }
    LinearGradientBrush& GetGradientBrushColor() { return m_gdiGradientBrush; }
    CPoint GetTopLeft() { return m_pointTopLeft; }
CPoint GetBottomRight() { return m_pointBottomRight; }

public:
    Graphics* m_pGraphics;

public:
    // GDI+ Drawing objects
    Color m_gdiColorWhite;
    Color m_gdiColorBlack;
    Color m_gdiColorLine;
    Color m_gdiColorFill;
    Pen m_gdiPenBlack;
    Pen m_gdiPenColor;
    SolidBrush m_gdiBrushColor;
    SolidBrush m_gdiBrushBlack;
    LinearGradientBrush m_gdiGradientBrush;

    // MFC Drawing objects
    CPoint m_pointTopLeft;
    CPoint m_pointBottomRight;
};


void CallDraw(CDrawingContext& ctxt, std::shared_ptr<CElement> pElement);

class CMethodData
{
public:
    bool m_IsPublic;
    std::wstring m_Name;
};

class CFieldData
{
public:
    bool m_IsPublic;
    std::wstring m_Type;
    std::wstring m_Name;
};

class CPropertyData
{
public:
    std::wstring m_Type;
    std::wstring m_Name;
};

class CTypeData
{
public:
    std::wstring m_Name;
    std::wstring m_FullName;
    std::vector<std::shared_ptr<CMethodData>> m_Methods;
    std::vector<std::shared_ptr<CFieldData>> m_Fields;
    std::vector<std::shared_ptr<CPropertyData>> m_Properties;
};

class CFactory
{
public:
    static std::shared_ptr<CElement> CreateElementOfType(ElementType type, ShapeType shapeType);
    // counter of objects
    static int g_counter;
};

class CElementManager : public CObject
{
private:

public:
    DECLARE_SERIAL(CElementManager);
    CElementManager();
    virtual ~CElementManager(void);

    // Attributes
public:
    // Drawing objects
    CElementContainer m_objects;
    // Selection objects
    CElementContainer m_selection;
    // Clipboard objects
    CElementContainer m_clipboard;

    COLORREF m_paperColor;
    // Page size in logical coordinates
    CSize m_size;
    CPoint m_lastPoint;
    // Current working object
    std::wstring m_objectId;
    // Current Select action
    SelectMode m_selectMode;
    // Cursor hanlde
    int m_nDragHandle;
    // Zoom float factor (default 1.0f)
    float m_fZoomFactor;

    // Attributes Current UI interaction members
public:
    // Is in drawing...
    BOOL m_bDrawing;
    // Current selected drawing tool
    ElementType m_type;
    // Current selected shape type from Ribbon
    ShapeType m_shapeType;

public:
    // Selection 1st point
    CPoint m_selectPoint;
    // Selection Rect
    CRect m_selectionRect;

    // Methods for Attributes
public:
    //SelectMode GetSelectMode()	 { return m_selectMode; }
    const vector<std::shared_ptr<CElement>>& GetObjects() { return m_objects.m_objects; }

    // Debugging Operations
public:
    void DebugDumpObjects(CModeler1View* pView);

    // Operations
public:
    void Serialize_LoadAsXML(CModeler1View* pView);
    void Serialize_SaveAsXML(CModeler1View* pView);
    void ConnectToMainFrame(CModeler1View* pView);
    void ConnectToPropertyGrid();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    void RemoveSelectedObjects(CModeler1View* pView);
    void ViewToManager(CModeler1View* pView, CPoint& point);
    void ViewToManager(CModeler1View* pView, CRect& rect);
    void ManagerToView(CModeler1View* pView, CPoint& point);
    void ManagerToView(CModeler1View* pView, CRect& rect);
    COLORREF GetPaperColor() const { return m_paperColor; }
    void Invalidate(CModeler1View* pView, std::shared_ptr<CElement> pElement);
    void Invalidate(CModeler1View* pView);
    void InvalObj(CModeler1View* pView, std::shared_ptr<CElement> pElement);
    CSize GetSize() const { return m_size; }
    void UpdateFromPropertyGrid(std::wstring objectId, std::wstring name, std::wstring value);
    void UpdateFromPropertyGrid(std::wstring objectId, std::wstring name, COLORREF color);
    void UpdateFromPropertyGrid(std::wstring objectId, std::wstring name, long value);
    void ActivateView(CModeler1View* pView, bool bActivate, CView* pActiveView, CView* pDeactiveView);

    // Managing Font operations
public:
    void OnFont(CModeler1View* pView);
    void OnFontSize(CModeler1View* pView);

    // Managing Clipboard operations
public:
    void OnEditCut(CModeler1View* pView);
    void OnEditCopy(CModeler1View* pView);
    void OnEditPaste(CModeler1View* pView);

    // Managing Object Positions
public:
    void MoveToFront(CModeler1View* pView);
    void MoveForward(CModeler1View* pView);
    void MoveBackward(CModeler1View* pView);
    void MoveToBack(CModeler1View* pView);

    // Managing Background drawing
public:
    void DrawBackground(CModeler1View* pView, CDC* pDC);

    // Managing UI object connections
public:
    void FindAConnectionFor(std::shared_ptr<CElement> pElement, CPoint point, CModeler1View* pView);

    // Managing UI dependencies (Ribbon UI, Property Grid, ClassView)
public:
    void UpdateUI(CModeler1View* pView, std::shared_ptr<CElement> pElement);
    void UpdateRibbonUI(CModeler1View* pView, std::shared_ptr<CElement> pElement);
    void UpdatePropertyGrid(CModeler1View* pView, std::shared_ptr<CElement> pElement);
    void UpdateClassView();
    void UpdateClassView(std::shared_ptr<CElement> pElement);
    void UpdateFileView();
    void UpdateFileView(std::shared_ptr<CElement> pElement);

    // Managing Object Format
public:
    void FillColor(CModeler1View* pView);
    void NoFillColor(CModeler1View* pView);
    void LineColor(CModeler1View* pView);
    void LineWidth(CModeler1View* pView, UINT nID);
    void PageColor(CModeler1View* pView);

    // Managing Zoom Operations
public:
    void Zoom(CModeler1View* pView);
    void ZoomIn(CModeler1View* pView);
    void ZoomOut(CModeler1View* pView);

    // Managing Object Selection
public:
    bool HasSelection();
    bool IsSelected(std::shared_ptr<CElement> pElement);
    bool Select(std::shared_ptr<CElement> pElement);
    bool Deselect(std::shared_ptr<CElement> pElement);
    void SelectNone();
    void DrawSelectionRect(CModeler1View* pView);

    // Overridables
public:
    virtual void PrepareDC(CModeler1View* pView, CDC* pDC, CPrintInfo* pInfo);
    virtual void Draw(CModeler1View* pView, CDC* pDC);
    virtual void DrawEx(CModeler1View* pView, CDC* pDC);
    virtual void Update(CModeler1View* pView, LPARAM lHint, CObject* pHint);

    // UI Handlers
public:
    virtual void OnLButtonDown(CModeler1View* pView, UINT nFlags, const CPoint& cpoint);
    virtual void OnLButtonDblClk(CModeler1View* pView, UINT nFlags, const CPoint& cpoint);
    virtual void OnLButtonUp(CModeler1View* pView, UINT nFlags, const CPoint& cpoint);
    virtual void OnMouseMove(CModeler1View* pView, UINT nFlags, const CPoint& cpoint);
};

// special 'list' class for this application(requires afxtempl.h)
typedef CTypedPtrList<CObList, CElement*> CElementList;

class CElementContainer : public CObject
{
private:

public:
    DECLARE_SERIAL(CElementContainer);
    CElementContainer();
    virtual ~CElementContainer(void);

    // Operations
public:
    virtual void Serialize(CElementManager* pElementManager, CArchive& ar);   // overridden for document i/o

// Operations
public:
    std::shared_ptr<CElement> FindElement(ElementType type);
    std::shared_ptr<CElement> FindElement(std::wstring objectId);
    bool FindElement(std::wstring objectId, vector<std::shared_ptr<CElement>>::iterator& it);
    std::shared_ptr<CElement> ObjectAt(const CPoint& point);
    void Remove(const CElementContainer& selection);
    void Copy(const CElementContainer& selection);
    void Clone(const CElementContainer& selection);
    void ChangeInnerAttributes();
    void CopyWithAttributesChange(const CElementContainer& selection);

    // Managing Object Positions
public:
    void MoveToFront(const CElementContainer& selection);
    void MoveForward(const CElementContainer& selection);
    void MoveBackward(const CElementContainer& selection);
    void MoveToBack(const CElementContainer& selection);

    // Debugging Operations
public:
    void DebugDumpObjects(CModeler1View* pView);

    // Operations MFC like
public:
    std::shared_ptr<CElement> GetHead();
    int GetCount();
    void RemoveAll();
    void Remove(std::shared_ptr<CElement> pElement);
    void AddTail(std::shared_ptr<CElement> pElement);

    // Attributes
public:
    vector<std::shared_ptr<CElement>> m_objects;
    //CElementList m_objects;	
};


// CDrawingElement command target

class CLineElement : public CElement
{
    //public:
    //	CLineElement();
    //	virtual ~CLineElement();
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CRectangleElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CTriangleElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CEllipseElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CArrowRightElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CArrowDownElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CStarElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CParentheseLeftElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CParentheseRightElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CLineBrokenElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CDevelopmentElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CImportElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);

public:
    std::shared_ptr<CTypeData> m_TypeData;
};

class CImageElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CInfrastructureElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CTextElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CSimpleTextElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CNotImplementedElement : public CElement
{
public:
    virtual void Draw(CDrawingContext& ctxt);
};

class CConnectableElement : public CElement
{
public:
};

#endif