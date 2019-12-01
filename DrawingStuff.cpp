#include "pch.h"
#include "MainFrm.h"
#include "DrawingStuff.h"
#include "MyDesktopDoc.h"
#include "StartMenuViewEx.h"

string ToUpper(string strToConvert)
{
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}

wstring ToUpper(wstring strToConvert)
{
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CGuid Class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGuid::CGuid()
{
#ifdef GUID_TRUE
    ::UuidCreateSequential(&m_uuid);
#endif
}

CGuid::~CGuid(void)
{
}

CString CGuid::ToString()
{
#ifdef GUID_TRUE
    unsigned char* sz;
    ::UuidToStringA(&m_uuid, &sz);
    CString str((const unsigned char*)sz);
    RpcStringFree(&sz);
    return str;
#else
    return _T("");
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CShapeType
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShapeType CShapeType::ToShapeType(int value)
{
    ShapeType ret = ShapeType::unknown;
    switch (value)
    {
    case line:
    case line_right:
    case rectangle:
    case ellipse:
    case rectangle_round:
    case triangle:
    case line_broken:
    case line_broken_right:
    case notimp_igloo:
    case notimpl_multi_line:
    case arrow_right:
    case arrow_down:
    case line2:
    case line_right2:
    case line_left_right:
    case parenthese_left:
    case parenthese_right:
    case star:
        ret = (ShapeType)value;
        break;
    case image_fixed:
    case image_scaled:
        ret = (ShapeType)value;
        break;
    case infrastructure_server_ad:
    case infrastructure_server:
    case infrastructure_server_web:
    case infrastructure_server_database:
    case infrastructure_workstation:
    case infrastructure_laptop:
    case infrastructure_firewall:
    case infrastructure_network:
    case infrastructure_virtual_server:
    case infrastructure_virtual_server_web:
    case infrastructure_virtual_server_database:
    case infrastructure_virtualization_server:
    case infrastructure_server_ad_grey:
    case infrastructure_server_grey:
    case infrastructure_server_database_grey:
    case infrastructure_server_farm:
    case infrastructure_workstation_grey:
    case infrastructure_laptop_grey:
        ret = (ShapeType)value;
        break;
    case text:
    case text_left:
    case text_center:
    case text_right:
    case text_justify:
        ret = (ShapeType)value;
        break;
    case development_class:
    case development_interface:
    case development_enumeration:
    case development_package:
    case development_comment:
    case development_association:
    case development_aggregation:
    case development_composition:
    case development_dependency:
    case development_inheritance:
    case development_package_import:
    case development_connector:
    case development_component:
        ret = (ShapeType)value;
        break;
    default: break;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDrawingContext Class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDrawingContext::CDrawingContext(std::shared_ptr<CElement> pElement)
    : m_gdiPenBlack(Color(255, 0, 0, 0)),
    m_gdiPenColor(Color(255, 0, 0, 0)),
    m_gdiBrushColor(m_gdiColorBlack),
    m_gdiBrushBlack(m_gdiColorBlack),
    m_gdiBrushWhite(m_gdiColorWhite),
    m_gdiRandomBrushColor(m_gdiColorBlack),
    m_gdiGradientBrush(
        Point(pElement->m_rect.left, pElement->m_rect.top),
        Point(pElement->m_rect.right, pElement->m_rect.bottom),
        m_gdiColorBlack,
        m_gdiColorBlack)
{
    m_gdiColorWhite.SetFromCOLORREF(Color::White);
    m_gdiColorBlack.SetFromCOLORREF(Color::Black);
    m_gdiColorLine.SetValue(Color::MakeARGB(255, GetRValue(pElement->m_colorLine), GetGValue(pElement->m_colorLine), GetBValue(pElement->m_colorLine)));
    m_gdiColorFill.SetValue(Color::MakeARGB(255, GetRValue(pElement->m_colorFill), GetGValue(pElement->m_colorFill), GetBValue(pElement->m_colorFill)));
    m_gdiPenBlack.SetColor(m_gdiColorBlack);
    m_gdiPenColor.SetColor(m_gdiColorLine);
    m_gdiPenColor.SetWidth(pElement->m_lineWidth);
    m_pointTopLeft = pElement->m_rect.TopLeft();
    m_pointBottomRight = pElement->m_rect.BottomRight();
    m_gdiBrushColor.SetColor(m_gdiColorFill);
    m_gdiBrushBlack.SetColor(m_gdiColorBlack);
    m_gdiBrushWhite.SetColor(m_gdiColorWhite);

    Color color1(255, 241, 247, 255);
    m_gdiGradientBrush.SetLinearColors(color1, m_gdiColorFill);
}


CDrawingContext::~CDrawingContext(void)
{
}

SolidBrush& CDrawingContext::GetRandomBrushColor()
{ 
    Color gdiColorFill(255, 0, 0, 0);
    gdiColorFill.SetValue(Color::MakeARGB(255, rand()%255, rand()% 255, rand()% 255));
    m_gdiRandomBrushColor.SetColor(gdiColorFill);
    return m_gdiRandomBrushColor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CFactory Class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CFactory::g_counter = 0;

std::shared_ptr<CElement> CFactory::CreateElementOfType(ElementType type, ShapeType shapeType)
{
    //std::shared_ptr<CElement> pNewElement = new CElement();
    std::shared_ptr<CElement> pNewElement = nullptr;
    //pNewElement = make_shared<CElement>();
    /*
    #ifdef USE_BOOST
        std::shared_ptr<CElement> pNewElement(new CElement());
    #else
        std::shared_ptr<CElement> pNewElement = make_shared<CElement>();
    #endif
    */
    if (type == ElementType::type_shapes_simple)
    {
        switch (shapeType)
        {
        case line:
        case line2:
        case line_right:
        case line_right2:
        case line_left_right:
        {
            std::shared_ptr<CElement> apNewElement(new CLineElement());
            pNewElement = apNewElement;
            break;
        }
        case rectangle:
        case rectangle_round:
        {
            std::shared_ptr<CElement> apNewElement(new CRectangleElement());
            pNewElement = apNewElement;
            break;
        }
        case triangle:
        {
            std::shared_ptr<CElement> apNewElement(new CTriangleElement());
            pNewElement = apNewElement;
            break;
        }
        case arrow_right:
        {
            std::shared_ptr<CElement> apNewElement(new CArrowRightElement());
            pNewElement = apNewElement;
            break;
        }
        case arrow_down:
        {
            std::shared_ptr<CElement> apNewElement(new CArrowDownElement());
            pNewElement = apNewElement;
            break;
        }
        case ellipse:
        {
            std::shared_ptr<CElement> apNewElement(new CEllipseElement());
            pNewElement = apNewElement;
            break;
        }
        case parenthese_left:
        {
            std::shared_ptr<CElement> apNewElement(new CParentheseLeftElement());
            pNewElement = apNewElement;
            break;
        }
        case parenthese_right:
        {
            std::shared_ptr<CElement> apNewElement(new CParentheseRightElement());
            pNewElement = apNewElement;
            break;
        }
        case star:
        {
            std::shared_ptr<CElement> apNewElement(new CStarElement());
            pNewElement = apNewElement;
            break;
        }
        case line_broken:
        case line_broken_right:
        {
            std::shared_ptr<CElement> apNewElement(new CLineBrokenElement());
            pNewElement = apNewElement;
            break;
        }
        case notimp_igloo:
        case notimpl_multi_line:
        default:
        {
            std::shared_ptr<CElement> apNewElement(new CNotImplementedElement());
            // Not implemented yet !
            pNewElement->m_type = ElementType::type_unknown;
            pNewElement = apNewElement;
            break;
        }
        }
    }

    if (type == ElementType::type_image)
    {
        switch (shapeType)
        {
        case image_fixed:
        case image_scaled:
        {
            std::shared_ptr<CElement> apNewElement(new CImageElement());
            pNewElement = apNewElement;
            break;
        }
        default:
        {
            std::shared_ptr<CElement> apNewElement(new CNotImplementedElement());
            pNewElement = apNewElement;
            // Not implemented yet !
            pNewElement->m_type = ElementType::type_unknown;
            break;
        }
        }
    }

    if (type == ElementType::type_shapes_infrastructure)
    {
        std::shared_ptr<CElement> apNewElement(new CImageElement());
        pNewElement = apNewElement;
        // No line around the object
        pNewElement->m_bColorLine = FALSE;

        switch (shapeType)
        {
        case ShapeType::infrastructure_server_ad:
            pNewElement->m_image = L"ServerAD.png";
            break;
        case ShapeType::infrastructure_server:
            pNewElement->m_image = L"Server.png";
            break;
        case ShapeType::infrastructure_server_web:
            pNewElement->m_image = L"ServerWeb.png";
            break;
        case ShapeType::infrastructure_server_database:
            pNewElement->m_image = L"ServerDatabase.png";
            break;
        case ShapeType::infrastructure_workstation:
            pNewElement->m_image = L"Workstation.png";
            break;
        case ShapeType::infrastructure_laptop:
            pNewElement->m_image = L"Laptop.png";
            break;
        case ShapeType::infrastructure_firewall:
            pNewElement->m_image = L"Firewall.png";
            break;
        case ShapeType::infrastructure_network:
            pNewElement->m_image = L"network.png";
            break;
        case infrastructure_virtual_server:
            pNewElement->m_image = L"Server_VM.png";
            break;
        case infrastructure_virtual_server_web:
            pNewElement->m_image = L"ServerWeb_VM.png";
            break;
        case infrastructure_virtual_server_database:
            pNewElement->m_image = L"ServerDatabase_VM.png";
            break;
        case infrastructure_virtualization_server:
            pNewElement->m_image = L"Virtualization_Server.png";
            break;
        case infrastructure_server_ad_grey:
            pNewElement->m_image = L"ServerAD_grey.png";
            break;
        case infrastructure_server_grey:
            pNewElement->m_image = L"Server_grey.png";
            break;
        case infrastructure_server_database_grey:
            pNewElement->m_image = L"ServerDatabase_grey.png";
            break;
        case infrastructure_server_farm:
            pNewElement->m_image = L"Server_Farm.png";
            break;
        case infrastructure_workstation_grey:
            pNewElement->m_image = L"Workstation_grey.png";
            break;
        case infrastructure_laptop_grey:
            pNewElement->m_image = L"Laptop_grey.png";
            break;
        default:
            // Not implemented yet !
            pNewElement->m_type = ElementType::type_unknown;
            break;
        }
    }

    if (type == ElementType::type_shapes_development)
    {
        std::shared_ptr<CElement> apNewElement(new CDevelopmentElement());
        pNewElement = apNewElement;
        pNewElement->m_bColorLine = true;
        pNewElement->m_bColorFill = true;
        pNewElement->m_bSolidColorFill = true;

        // Set colors for development shapes
        Color colorLineClass(255, 52, 101, 164);
        Color colorFillClass(255, 200, 210, 233);
        Color colorLineInterface(255, 176, 167, 129);
        Color colorFillInterface(255, 217, 230, 203);
        Color colorLineEnumeration(255, 112, 88, 41);
        Color colorFillEnumeration(255, 175, 165, 120);
        Color colorLinePackage(255, 191, 161, 132);
        Color colorFillPackage(255, 255, 251, 240);
        Color colorLineComment(255, 202, 178, 45);
        Color colorFillComment(255, 251, 247, 200);
        Color colorLineComponent(255, 83, 134, 191);
        Color colorFillComponent(255, 181, 210, 237);

        switch (shapeType)
        {
        case development_class:
            pNewElement->m_text = L"Class";
            pNewElement->m_colorFill = colorFillClass.ToCOLORREF();
            pNewElement->m_colorLine = colorLineClass.ToCOLORREF();
            break;
        case development_interface:
            pNewElement->m_text = L"Interface";
            pNewElement->m_colorFill = colorFillInterface.ToCOLORREF();
            pNewElement->m_colorLine = colorLineInterface.ToCOLORREF();
            break;
        case development_enumeration:
            pNewElement->m_text = L"Enumeration";
            pNewElement->m_colorFill = colorFillEnumeration.ToCOLORREF();
            pNewElement->m_colorLine = colorLineEnumeration.ToCOLORREF();
            break;
        case development_package:
            pNewElement->m_text = L"Package";
            pNewElement->m_colorFill = colorFillPackage.ToCOLORREF();
            pNewElement->m_colorLine = colorLinePackage.ToCOLORREF();
            break;
        case development_comment:
            pNewElement->m_text = L"Comment";
            pNewElement->m_colorFill = colorFillComment.ToCOLORREF();
            pNewElement->m_colorLine = colorLineComment.ToCOLORREF();
            break;
        case development_component:
            pNewElement->m_text = L"Component";
            pNewElement->m_colorFill = colorFillComponent.ToCOLORREF();
            pNewElement->m_colorLine = colorLineComponent.ToCOLORREF();
            break;
        case development_association:
        case development_aggregation:
        case development_composition:
        case development_dependency:
        case development_inheritance:
        case development_package_import:
        case development_connector:
            break;
        }
    }

    if (type == ElementType::type_shapes_import)
    {
        std::shared_ptr<CElement> apNewElement = make_shared<CImportElement>();
        pNewElement = apNewElement;
        pNewElement->m_bColorLine = true;
        pNewElement->m_bColorFill = true;
        pNewElement->m_bSolidColorFill = true;

        // Set same colors like development shapes
        Color colorLineClass(255, 52, 101, 164);
        Color colorFillClass(255, 200, 210, 233);

        switch (shapeType)
        {
        case import_class:
            pNewElement->m_text = L"";
            pNewElement->m_colorFill = colorFillClass.ToCOLORREF();
            pNewElement->m_colorLine = colorLineClass.ToCOLORREF();
            break;
        }
    }

    if (type == ElementType::type_text)
    {
        std::shared_ptr<CElement> apNewElement(new CTextElement());
        pNewElement = apNewElement;

        pNewElement->m_bColorLine = true;
        pNewElement->m_bColorFill = false;
        pNewElement->m_bSolidColorFill = true;
        pNewElement->m_text = L"<type text>";
    }

    if (type == ElementType::type_image)
    {
        std::shared_ptr<CElement> apNewElement(new CImageElement());
        pNewElement = apNewElement;
        // No line around the object
        pNewElement->m_bColorLine = FALSE;
    }

    if (type == ElementType::type_start_menu)
    {
        std::shared_ptr<CStartMenuElement> apNewElement = make_shared<CStartMenuElement>();
        pNewElement = apNewElement;
        pNewElement->m_bColorLine = true;
        pNewElement->m_bColorFill = true;
        pNewElement->m_bSolidColorFill = true;

        // Set same colors like development shapes
        Color colorLineClass(255, 52, 101, 164);
        Color colorFillClass(255, 200, 210, 233);

        switch (shapeType)
        {
        case start_menu_element:
            pNewElement->m_text = L"";
            pNewElement->m_colorFill = RGB(rand() % 255, rand() % 255, rand() % 255);
            pNewElement->m_colorLine = colorLineClass.ToCOLORREF();
            break;
        }
    }

    //
    // Initialize default members for the element
    //
    pNewElement->m_type = type;
    pNewElement->m_shapeType = shapeType;
    return pNewElement;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CElement Class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CElement, CObject, 0)

int CElement::m_counter = 0;

CElement::CElement()
{
    m_pManager = NULL;
    m_pView = NULL;

    m_shapeType = ShapeType::unknown;
    m_rect.SetRectEmpty();
    m_point = CPoint(0, 0);
    m_last = m_point;
    m_text = L"";
    m_bColorFill = true;
    m_colorFill = RGB(154, 200, 249);
    m_bSolidColorFill = false;
    m_bColorLine = true;
    m_colorLine = RGB(0, 0, 0);
    m_bLineWidth = true;
    m_lineWidth = 1;
    m_image = L"";
    m_fontName = L"Calibri";
    m_fontSize = 12;

    m_bMoving = FALSE;
    m_type = ElementType::type_unknown;
    m_shapeType = ShapeType::unknown;

    SetGuid();
    SetName();
}

CElement::~CElement(void)
{
}

void CElement::SetGuid()
{
    USES_CONVERSION;

    m_counter++;

    CGuid guid;
#ifdef GUID_TRUE
    m_objectId = guid.ToString();
#else
    SYSTEMTIME st;
    GetSystemTime(&st);
    CTime dt = CTime::GetCurrentTime();
    CString objectId;
    objectId.Format(_T("guid_%d_%s_%03d_%ld"), m_counter, dt.Format(_T("%H%M%S")), st.wMilliseconds, GetTickCount());
    this->m_objectId = T2W((LPTSTR)(LPCTSTR)objectId);
#endif
}

void CElement::SetName()
{
    USES_CONVERSION;

    // Inc counter of created objects
    CFactory::g_counter++;
    // element name
    CTime dt = CTime::GetCurrentTime();
    CString name;
    name.Format(_T("Element n_%d"), CFactory::g_counter); //_%s.%03d", dt.Format("%H%M%S"), tm.wMilliseconds);
    this->m_name = T2W((LPTSTR)(LPCTSTR)name);
}

std::shared_ptr<CElement> CElement::MakeCopy()
{
    std::shared_ptr<CElement> pNewElement = CFactory::CreateElementOfType((ElementType)this->m_type,
        (ShapeType)this->m_shapeType);
    pNewElement->m_name = this->m_name;
    pNewElement->m_objectId = this->m_objectId;
    pNewElement->m_caption = this->m_caption;
    pNewElement->m_text = this->m_text;
    pNewElement->m_lineWidth = this->m_lineWidth;
    pNewElement->m_pManager = this->m_pManager;
    pNewElement->m_pView = this->m_pView;
    pNewElement->m_rect = this->m_rect;
    pNewElement->m_bColorFill = m_bColorFill;
    pNewElement->m_bColorLine = m_bColorLine;
    pNewElement->m_bLineWidth = m_bLineWidth;
    pNewElement->m_bSolidColorFill = m_bSolidColorFill;
    pNewElement->m_colorFill = m_colorFill;
    pNewElement->m_colorLine = m_colorLine;

    return pNewElement;
}

void CElement::Serialize(CArchive& ar)
{
    USES_CONVERSION;

    if (ar.IsStoring())
    {
        CString name = W2T((LPTSTR)m_name.c_str());
        ar << name;
        int type = m_type;
        ar << type;
        int shapeType = m_shapeType;
        ar << shapeType;
        CString objectId = W2T((LPTSTR)m_objectId.c_str());
        ar << objectId;
        CString caption = W2T((LPTSTR)m_caption.c_str());
        ar << caption;
        CString text = W2T((LPTSTR)m_text.c_str());
        ar << text;
        ar << m_rect;
        ar << m_point;
        ar << m_last;
        ar << m_colorFill;
        ar << m_bColorFill;
        ar << m_colorLine;
        ar << m_bColorLine;
        ar << m_bColorLine;
        ar << m_lineWidth;
        CString image = W2T((LPTSTR)m_image.c_str());
        ar << image;
    }
    else
    {
        // get the document back pointer from the archive
        //CModeler1Doc* pDocument = (CModeler1Doc*)ar.m_pDocument;
        //m_pManager = pDocument->GetManager();

        CString name;
        ar >> name;
        this->m_name = T2W((LPTSTR)(LPCTSTR)name);
        int type;
        ar >> type;
        m_type = (ElementType)type;
        int shapeType;
        ar >> shapeType;
        m_shapeType = (ShapeType)shapeType;
        CString objectId;
        ar >> objectId;
        this->m_objectId = T2W((LPTSTR)(LPCTSTR)objectId);
        CString caption;
        ar >> caption;
        this->m_caption = T2W((LPTSTR)(LPCTSTR)caption);
        CString text;
        ar >> text;
        this->m_text = T2W((LPTSTR)(LPCTSTR)text);
        ar >> m_rect;
        ar >> m_point;
        ar >> m_last;
        ar >> m_colorFill;
        ar >> m_bColorFill;
        ar >> m_colorLine;
        ar >> m_bColorLine;
        ar >> m_bColorLine;
        ar >> m_lineWidth;
        CString image;
        ar >> image;
        this->m_image = T2W((LPTSTR)(LPCTSTR)image);
    }
}

CString CElement::ToString()
{
    CString str;
    str.Format(_T("Element name=<%s> id={%s} type=<%s> shape=<%s> rect={%d,%d,%d,%d} caption=<%s> text=<%s> image=<%s> colorFill={%03d%03d%03d} colorLine={%03d%03d%03d}"),
        m_name.c_str(), m_objectId.c_str(), ToString(m_type), ToString(m_shapeType),
        m_rect.left, m_rect.top, m_rect.right, m_rect.bottom,
        m_caption.c_str(), m_text.c_str(), m_image.c_str(),
        GetRValue(m_colorFill), GetGValue(m_colorFill), GetBValue(m_colorFill),
        GetRValue(m_colorLine), GetGValue(m_colorLine), GetBValue(m_colorLine));
    return str;
}

CString CElement::ToString(ElementType type)
{
    CString str = _T("");
    switch (type)
    {
    case ElementType::type_unknown:
        str = _T("type_unknown->not implemented yet");
        break;

    case ElementType::type_shapes_simple:
        str = _T("type_shapes_simple");
        break;

    case ElementType::type_image:
        str = _T("type_image");
        break;

    case ElementType::type_shapes_infrastructure:
        str = _T("type_shapes_infrastructure");
        break;

    case ElementType::type_text:
        str = _T("type_text");
        break;

    case ElementType::type_shapes_development:
        str = _T("type_shapes_development");
        break;

    default:
        break;
    }
    return str;
}

CString CElement::ToString(ShapeType type)
{
    CString str = _T("");
    switch (type)
    {
    case line:
        str = _T("line");
        break;
    case line_right:
        str = _T("line_right");
        break;
    case rectangle:
        str = _T("rectangle");
        break;
    case ellipse:
        str = _T("ellipse");
        break;
    case rectangle_round:
        str = _T("rectangle_round");
        break;
    case triangle:
        str = _T("triangle");
        break;
    case line_broken:
        str = _T("line_broken");
        break;
    case line_broken_right:
        str = _T("line_broken_right");
        break;
    case line2:
        str = _T("line2");
        break;
    case line_right2:
        str = _T("line_right2");
        break;
    case line_left_right:
        str = _T("line_left_right");
        break;
    case arrow_right:
        str = _T("arrow_right");
        break;
    case arrow_down:
        str = _T("arrow_down");
        break;
    case parenthese_left:
        str = _T("parenthese_left");
        break;
    case parenthese_right:
        str = _T("parenthese_right");
        break;
    case star:
        str = _T("star");
        break;

    case image_fixed:
        str = _T("image_fixed");
        break;
    case image_scaled:
        str = _T("image_scaled");
        break;

    case infrastructure_server_ad:
        str = _T("infrastructure_server_ad");
        break;
    case infrastructure_server:
        str = _T("infrastructure_server");
        break;
    case infrastructure_server_web:
        str = _T("infrastructure_server_web");
        break;
    case infrastructure_server_database:
        str = _T("infrastructure_server_web");
        break;
    case infrastructure_workstation:
        str = _T("infrastructure_workstation");
        break;
    case infrastructure_laptop:
        str = _T("infrastructure_laptop");
        break;
    case infrastructure_firewall:
        str = _T("infrastructure_firewall");
        break;
    case infrastructure_network:
        str = _T("infrastructure_network");
        break;
    case infrastructure_virtual_server:
        str = _T("infrastructure_virtual_server");
        break;
    case infrastructure_virtual_server_web:
        str = _T("infrastructure_virtual_server_web");
        break;
    case infrastructure_virtual_server_database:
        str = _T("infrastructure_virtual_server_database");
        break;
    case infrastructure_virtualization_server:
        str = _T("infrastructure_virtualization_server");
        break;
    case infrastructure_server_ad_grey:
        str = _T("infrastructure_server_ad");
        break;
    case infrastructure_server_grey:
        str = _T("infrastructure_server");
        break;
    case infrastructure_server_database_grey:
        str = _T("infrastructure_server_database");
        break;
    case infrastructure_server_farm:
        str = _T("infrastructure_server_farm");
        break;
    case infrastructure_workstation_grey:
        str = _T("infrastructure_workstation");
        break;
    case infrastructure_laptop_grey:
        str = _T("infrastructure_laptop");
        break;

    case text:
        str = _T("text");
        break;
    case text_left:
        str = _T("text_left");
        break;
    case text_center:
        str = _T("text_center");
        break;
    case text_right:
        str = _T("text_right");
        break;
    case text_justify:
        str = _T("text_justify");
        break;

    case development_class:
        str = _T("development_class");
        break;
    case development_interface:
        str = _T("development_interface");
        break;
    case development_enumeration:
        str = _T("development_enumeration");
        break;
    case development_package:
        str = _T("development_package");
        break;
    case development_comment:
        str = _T("development_comment");
        break;
    case development_association:
        str = _T("development_association");
        break;
    case development_aggregation:
        str = _T("development_aggregation");
        break;
    case development_composition:
        str = _T("development_composition");
        break;
    case development_dependency:
        str = _T("development_dependency");
        break;
    case development_inheritance:
        str = _T("development_inheritance");
        break;
    case development_package_import:
        str = _T("development_package_import");
        break;
    case development_connector:
        str = _T("development_connector");
        break;
    case development_component:
        str = _T("development_component");
        break;
    }
    return str;
}

/*
bool CElement::IsDrawable(ElementType type)
{
    bool ret = false;
    switch(type)
    {
        case ElementType::type_rectangle:
        case ElementType::type_class:
        case ElementType::type_line:
        case ElementType::type_ellipse:
        case ElementType::type_image:
        case ElementType::type_shapes:
            ret = true;
        break;
    }
    return ret;
}
*/

bool CElement::CanChangeFillColor() const
{
    return true;
}

bool CElement::CanChangeLineColor() const
{
    return true;
}

bool CElement::CanChangeLineWidth() const
{
    return true;
}

bool CElement::Intersects(const CRect& rect)
{
    CRect fixed = m_rect;
    CSize addSize(5, 5);
    fixed.InflateRect(addSize);
    fixed.NormalizeRect();
    CRect rectT = rect;
    rectT.NormalizeRect();

    // Debug
#ifdef DRAW_EXTERNAL_RECTANGLE_HITS
    //CClientDC dc(this->m_pView);
    //Graphics graphics(dc.m_hDC);
    //
    //Color colorBlack(255, 0, 0, 0);
    //Pen penBlack(colorBlack);

    //CRect rect1 = fixed;
    //CRect rect2 = rectT;
    //CRect rect3 = rect1 & rect2;

    //GetManager()->ManagerToView(this->m_pView, rect1);
    //GetManager()->ManagerToView(this->m_pView, rect2);
    //GetManager()->ManagerToView(this->m_pView, rect3);
    //graphics.DrawRectangle(&penBlack, rect1.left, rect1.top, rect1.Width(), rect1.Height());
    //graphics.DrawRectangle(&penBlack, rect2.left, rect2.top, rect2.Width(), rect2.Height());
    //graphics.DrawRectangle(&penBlack, rect3.left, rect3.top, rect3.Width(), rect3.Height());
#endif

    return !(rectT & fixed).IsRectEmpty();
}

bool CElement::IsLine()
{
    if (m_shapeType == ShapeType::line || m_shapeType == ShapeType::line2 ||
        m_shapeType == ShapeType::line_left_right ||
        m_shapeType == ShapeType::line_broken || m_shapeType == line_broken_right ||
        m_shapeType == ShapeType::line_right || m_shapeType == ShapeType::line_right2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CElement::InvalidateObj(void)
{
    this->m_rect.SetRect(this->m_point, this->m_last);
    if (IsLine())
    {
    }
    else
    {
        // rectangle
        this->m_rect.NormalizeRect();
    }
}

void CElement::CheckForKeepingAMinimumSize()
{
    const int defaultSize = 10;

    // For all types
    if (m_type == type_shapes_simple || m_type == type_image) //m_type == type_shapes_infrastructure ) //||  )
    {
        if (m_rect.Width() < defaultSize && m_rect.Height() < defaultSize)
        {
            CPoint p1 = m_rect.TopLeft();
            CPoint p2;
            p2.x = p1.x + defaultSize;
            p2.y = p1.y + defaultSize;
            m_rect.SetRect(p1, p2);
        }
    }
}

// Selection & Tracker helpers

int CElement::GetHandleCount()
{
    if (IsLine())
    {
        return 2; //8;
    }
    else
        return 8;
}

int CElement::HitTest(CPoint point, CStartMenuViewEx* pView, bool bSelected)
{
    CString str;
    if (bSelected)
    {
        int nHandleCount = GetHandleCount();
        for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
        {
            // GetHandleRect returns in logical coords
            CRect rc = GetHandleRect(nHandle, pView);

            // Debugging
            //str.Format(_T("HitTest try point{%d,%d} in rect{%d,%d,%d,%d}"), point.x, point.y, rc.left, rc.top, rc.right, rc.bottom);
            //pView->LogDebug(str);

            CRect rect(point, CSize(1, 1));
            CRect fixed = rc;
            CSize addSize(5, 5);
            fixed.InflateRect(addSize);
            fixed.NormalizeRect();
            if ((rect & fixed).IsRectEmpty() == FALSE)
            {
                // Debugging
                //str.Format("HitTest returns %d", nHanlde);
                //pView->LogDebug(str);
                return nHandle;
            }

            //if (point.x >= rc.left && point.x < rc.right && point.y <= rc.top && point.y > rc.bottom)
            //	return nHandle;
        }
    }
    else
    {
        if (point.x >= m_rect.left && point.x < m_rect.right && point.y <= m_rect.top && point.y > m_rect.bottom)
            return 1;
    }

    return 0;
}

// return rectange of handle in logical coords
CRect CElement::GetHandleRect(int nHandleID, CStartMenuViewEx* pView)
{
    CRect rect;

    // get the center of the handle in logical coords
    CPoint point = GetHandle(nHandleID);
    // convert to client/device coords
    GetManager()->ManagerToView(pView, point);
    //pView->DocToClient(point);
    // return CRect of handle in device coords
    rect.SetRect(point.x - 3, point.y - 3, point.x + 3, point.y + 3);
    //pView->ClientToDoc(rect);
    GetManager()->ViewToManager(pView, rect);

    return rect;
}

// returns logical coords of center of handle
CPoint CElement::GetHandle(int nHandle)
{
    // lines have only two dots tracker !
    if (IsLine() && nHandle == 2)
        nHandle = 5;

    int x, y, xCenter, yCenter;
    CRect rect = m_rect;

    // this gets the center regardless of left/right and top/bottom ordering
    xCenter = rect.left + rect.Width() / 2;
    yCenter = rect.top + rect.Height() / 2;

    switch (nHandle)
    {
    default:
        ASSERT(FALSE);

    case 1:
        x = rect.left;
        y = rect.top;
        break;

    case 2:
        x = xCenter;
        y = rect.top;
        break;

    case 3:
        x = rect.right;
        y = rect.top;
        break;

    case 4:
        x = rect.right;
        y = yCenter;
        break;

    case 5:
        x = rect.right;
        y = rect.bottom;
        break;

    case 6:
        x = xCenter;
        y = rect.bottom;
        break;

    case 7:
        x = rect.left;
        y = rect.bottom;
        break;

    case 8:
        x = rect.left;
        y = yCenter;
        break;
    }

    return CPoint(x, y);
}

HCURSOR CElement::GetHandleCursor(int nHandle)
{
    // lines have only two dots tracker !
    if (IsLine() && nHandle == 2)
        nHandle = 5;

    LPCTSTR id;
    switch (nHandle)
    {
    case 1:
    case 5:
        id = IDC_SIZENWSE;
        break;

    case 2:
    case 6:
        id = IDC_SIZENS;
        break;

    case 3:
    case 7:
        id = IDC_SIZENESW;
        break;

    case 4:
    case 8:
        id = IDC_SIZEWE;
        break;

    default:
        id = IDC_ARROW;
        //ASSERT(FALSE);
        break;
    }

    return AfxGetApp()->LoadStandardCursor(id);
}

// point must be in logical
void CElement::MoveHandleTo(int nHandle, CPoint point, CStartMenuViewEx* pView)
{
    // lines have only two dots tracker !
    if (IsLine() && nHandle == 2)
        nHandle = 5;

    CRect position = m_rect;
    switch (nHandle)
    {
    case 1:
        position.left = point.x;
        position.top = point.y;
        break;

    case 2:
        position.top = point.y;
        break;

    case 3:
        position.right = point.x;
        position.top = point.y;
        break;

    case 4:
        position.right = point.x;
        break;

    case 5:
        position.right = point.x;
        position.bottom = point.y;
        break;

    case 6:
        position.bottom = point.y;
        break;

    case 7:
        position.left = point.x;
        position.bottom = point.y;
        break;

    case 8:
        position.left = point.x;
        break;

    default:
        ASSERT(FALSE);
    }

    m_rect = position;

}

void CElement::DrawTracker(CDrawingContext& ctxt, TrackerState state)
{
    Color colorBlack(255, 0, 0, 0);
    SolidBrush solidBrush(colorBlack);
    CRect rect = m_rect;

    switch (state)
    {
    case normal:
        break;

    case selected:
    case active:
    {
        int nHandleCount = GetHandleCount();
        for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
        {
            CPoint handle = GetHandle(nHandle);
            //pDC->PatBlt(handle.x - 3, handle.y - 3, 7, 7, DSTINVERT);
            ctxt.GetGraphics()->FillRectangle(&solidBrush, handle.x - 3, handle.y - 3, 7, 7);
        }
    }
    break;
    }
}

std::wstring CElement::GetImageFilePath()
{
    std::wstring ret = L"";

    // FIXME
    std::wstring strShapePath = L"Images\\Shapes\\";
    if (this->m_type == ElementType::type_shapes_infrastructure)
    {
        ret = strShapePath + m_image;
    }
    else
    {
        ret = m_image;
    }
    return ret;
}

void CElement::Draw(CDrawingContext& ctxt)
{
    // Nothing to implement
    Color colorBlack(255, 0, 0, 0);
    Pen penBlack(colorBlack);
    CRect rect = m_rect;
    ctxt.GetGraphics()->DrawRectangle(&penBlack, rect.left, rect.top, rect.Width(), rect.Height());

    // Debug Only
    CString str;
    str.Format(_T("CElement::Draw()"));
    //m_pView->LogDebug(str);
    //AfxMessageBox(str);
}

void CallDraw(CDrawingContext& ctxt, std::shared_ptr<CElement> pElement)
{
    pElement->Draw(ctxt);
}

void CElement::Draw(CStartMenuViewEx* pView, CDC* pDC)
{
    Graphics graphics(pDC->m_hDC);
    //graphics.ScaleTransform(0.75f, 0.75f);
    graphics.ScaleTransform(GetManager()->m_fZoomFactor, GetManager()->m_fZoomFactor);

    //graphics.SetRenderingOrigin(0, 0);
    //graphics.RotateTransform(45.0);
    //graphics.RotateTransform(5.0f); //, MatrixOrderAppend);  // then rotate

#ifdef DRAW_DIRECLY_A_LINE
    {
        if (m_type == ElementType::type_shapes_simple)
        {
            if (IsLine())
            {
                CRect rect = m_rect;
                //rect.NormalizeRect();
                CPoint p1 = rect.TopLeft();
                CPoint p2 = rect.BottomRight();

                // Color for line
                Color colorLine(255, GetRValue(m_colorLine), GetGValue(m_colorLine), GetBValue(m_colorLine));
                Pen penLine(colorLine);
                graphics.DrawLine(&penLine, p1.x, p1.y, p2.x, p2.y);
                return;
            }
        }
    }
#endif

    CRect rect = m_rect;
    //rect.NormalizeRect();
    CPoint p1 = rect.TopLeft();
    CPoint p2 = rect.BottomRight();
    CPoint pointText(rect.left + 10, rect.top + 10);
    // RectF object for Text
    PointF pointF(p1.x, p1.y);
    SizeF sizeF(rect.Width(), rect.Height());
    RectF rectF(pointF, sizeF);

    Color colorWhite(255, 255, 255, 255);
    // Set gradient color
    Color color1(255, 241, 247, 255);
    Color color2(255, GetRValue(m_colorFill), GetGValue(m_colorFill), GetBValue(m_colorFill));
    // Set the color along the entire boundary of the path to aqua.
    LinearGradientBrush lgBrush(Point(rect.left, rect.top),
        Point(rect.right, rect.bottom),
        color1,
        color2);
    //Pen pen(&lgBrush);
    Color colorBlack(255, 0, 0, 0);
    Pen penBlack(colorBlack);
    // Color for line
    Color colorLine(255, GetRValue(m_colorLine), GetGValue(m_colorLine), GetBValue(m_colorLine));
    Pen penLine(colorLine);
    // Color for and Width
    int m_width = m_lineWidth;// FIXME m_8;
    Pen colorPen(colorLine, m_width);
    // Color for fill
    Color colorFill(255, GetRValue(m_colorFill), GetGValue(m_colorFill), GetBValue(m_colorFill));
    SolidBrush solidBrush(colorFill);
    SolidBrush solidBrushWhite(colorWhite);

    //
    // Moving an object means drawing a single dash-dot rectangle 
    //
    //if( this->m_bMoving == true )
    //{
    //	penBlack.SetDashStyle(DashStyleDot);
    //	
    //	if( IsLine() )
    //	{
    //		graphics.DrawLine(&penBlack, p1.x, p1.y, p2.x, p2.y);
    //	}
    //	else
    //	{
    //		graphics.DrawRectangle(&penBlack, rect.left, rect.top, rect.Width(), rect.Height());
    //	}
    //	return;
    //}

    //if( m_type == ElementType::type_shapes_simple )
    {
        //if( m_shapeType == ShapeType::line ||  m_shapeType == ShapeType::line2 )
        //{
        //	graphics.DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);
        //}
        //else 
        //if( m_shapeType == ShapeType::line_broken ||  m_shapeType == line_broken_right )
        //{
        //	// 1 * * * 2 * * * * *
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// * * * * 3 * * * * 4
        //	int step1_5_x = rect.Width() / 5;
        //	int step1_5_y = rect.Height() / 5;
        //	Point points[4] = {	Point(rect.left, rect.top), 
        //						Point(rect.left + rect.Width()/2, rect.top), 
        //						Point(rect.left + rect.Width()/2, rect.bottom), 
        //						Point(rect.right, rect.bottom)};
        //	int npoints = 4;

        //	if( m_shapeType == line_broken_right )
        //	{
        //		//colorPen.SetEndCap(LineCapArrowAnchor);
        //		//Create a Path, and add two lines to it.
        //		Point points[3] = {Point(-5, -5), Point(0, 0), Point(5, -5)};
        //		GraphicsPath capPath;
        //		capPath.AddLines(points, 3);
        //		// Create a CustomLineCap object.
        //		CustomLineCap custCap(NULL, &capPath); 
        //		// Set the start and end caps for custCap.
        //		custCap.SetStrokeCap(LineCapTriangle);
        //		// Create a Pen object, assign startStrokeCap and endStrokeCap as the 
        //		// start and end caps, and draw a line.
        //		colorPen.SetCustomEndCap(&custCap);
        //	}
        //	
        //	graphics.DrawLines(&colorPen, points, npoints);
        //}
        //else
        //if( m_shapeType == ShapeType::line_right || m_shapeType == ShapeType::line_right2 )
        //{
        //	//colorPen.SetEndCap(LineCapArrowAnchor);
        //	//graphics.DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);

        //	//Create a Path, and add two lines to it.
        //	Point points[3] = {Point(-5, -5), Point(0, 0), Point(5, -5)};
        //	GraphicsPath capPath;
        //	capPath.AddLines(points, 3);

        //	// Create a CustomLineCap object.
        //	CustomLineCap custCap(NULL, &capPath); 
  // 
        //	// Set the start and end caps for custCap.
        //	custCap.SetStrokeCap(LineCapTriangle);

        //	// Create a Pen object, assign startStrokeCap and endStrokeCap as the 
        //	// start and end caps, and draw a line.
        //	colorPen.SetCustomEndCap(&custCap);
        //	graphics.DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);

        //}
        //else if( m_shapeType == ShapeType::line_left_right )
        //{
        //	colorPen.SetStartCap(LineCapArrowAnchor);
        //	colorPen.SetEndCap(LineCapArrowAnchor);
        //	graphics.DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);
        //}
        //else if( m_shapeType == ShapeType::rectangle || m_shapeType == ShapeType::rectangle_round )
        //{
        //	if( HasColorFill() )
        //	{
        //		if( IsSolidColorFill() )
        //			graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        //		else
        //			graphics.FillRectangle(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());
        //	}
        //	if( HasColorLine() )
        //	{
        //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
        //	}
        //}
        //else if( m_shapeType == ShapeType::triangle )
        //{
        //	Point points[3] = {Point(rect.left + rect.Width()/2, rect.top), 
        //					Point(rect.right, rect.bottom), 
        //					Point(rect.left, rect.bottom)};
        //	if( HasColorFill() )
        //	{
        //		if( IsSolidColorFill() )
        //			graphics.FillPolygon(&solidBrush, points, 3);
        //		else
        //			graphics.FillPolygon(&lgBrush, points, 3);
        //	}
        //	if( HasColorLine() )
        //	{
        //		graphics.DrawPolygon(&colorPen, points, 3);
        //	}
        //}
        //else if( m_shapeType == ShapeType::arrow_right )
        //{
        //	// * * * * 3 * * * * *
        //	// 1 - - - 2 * * * * *
        //	// - * * * * * * * * 4
        //	// 7 - - - 6 * * * * *
        //	// * * * * 5 * * * * *

        //	int step1_5_x = rect.Width() / 5;
        //	int step1_5_y = rect.Height() / 5;
        //	Point points[7] = {	Point(rect.left, rect.top + step1_5_y), 
        //						Point(rect.left + step1_5_x*3, rect.top + step1_5_y), 
        //						Point(rect.left + step1_5_x*3, rect.top), 
        //						Point(rect.right, rect.top + rect.Height()/2),
        //						Point(rect.left + step1_5_x*3, rect.bottom), 
        //						Point(rect.left + step1_5_x*3, rect.bottom - step1_5_y),
        //						Point(rect.left, rect.bottom - step1_5_y)};
        //	int npoints = 7;
        //	if( HasColorFill() )
        //	{
        //		if( IsSolidColorFill() )
        //			graphics.FillPolygon(&solidBrush, points, npoints);
        //		else
        //			graphics.FillPolygon(&lgBrush, points, npoints);
        //	}
        //	if( HasColorLine() )
        //	{
        //		graphics.DrawPolygon(&colorPen, points, npoints);
        //	}
        //}
        //else if( m_shapeType == ShapeType::arrow_down )
        //{
        //	// * * 1 * * * 2 * * *
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// 6 * 7 * * * 3 * * 4
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// * * * * 5 * * * * *

        //	int step1_5_x = rect.Width() / 5;
        //	int step1_5_y = rect.Height() / 5;
        //	Point points[7] = {	/*1*/ Point(rect.left + step1_5_x*1, rect.top), 
        //						/*2*/ Point(rect.left + step1_5_x*4, rect.top), 
        //						/*3*/ Point(rect.left + step1_5_x*4, rect.top + step1_5_y*3), 
        //						/*4*/ Point(rect.right, rect.top + step1_5_y*3),
        //						/*5*/ Point(rect.left + rect.Width()/2, rect.bottom), 
        //						/*6*/ Point(rect.left, rect.top + step1_5_y*3),
        //						/*7*/ Point(rect.left + step1_5_x*1, rect.top + step1_5_y*3)};

        //	int npoints = 7;
        //	if( HasColorFill() )
        //	{
        //		if( IsSolidColorFill() )
        //			graphics.FillPolygon(&solidBrush, points, npoints);
        //		else
        //			graphics.FillPolygon(&lgBrush, points, npoints);
        //	}
        //	if( HasColorLine() )
        //	{
        //		graphics.DrawPolygon(&colorPen, points, npoints);
        //	}
        //}
        //else if( m_shapeType == ShapeType::star )
        //{
        //	// * * * * 1 * * * * *
        //	// * * * * * * * * * *
        //	// 3 * 2 * * * *10 * 9
        //	// * * * * * * * * * *
        //	// * * 4 * * * * 8 * *
        //	// * * * * * * * * * *
        //	// * * * * 6 * * * * *
        //	// * * * * * * * * * *
        //	// * * * * * * * * * *
        //	// 5 * * * * * * * * 7

        //	int step1_10_x = rect.Width() / 10;
        //	int step1_10_y = rect.Height() / 10;
        //	Point points[10] = {/*1*/ Point(rect.left + rect.Width()/2, rect.top), 
        //						/*2*/ Point(rect.left + step1_10_x*3, rect.top + step1_10_y*3), 
        //						/*3*/ Point(rect.left, rect.top + step1_10_y*3), 
        //						/*4*/ Point(rect.left + step1_10_x*3, rect.top + step1_10_y*5), 
        //						/*5*/ Point(rect.left, rect.bottom), 							
        //						/*6*/ Point(rect.left + rect.Width()/2, rect.top + step1_10_y*7), 
        //						/*7*/ Point(rect.right, rect.bottom),
        //						/*8*/ Point(rect.left + step1_10_x*7, rect.top + step1_10_y*5), 
        //						/*9*/ Point(rect.right, rect.top + step1_10_y*3), 
        //						/*10*/Point(rect.left + step1_10_x*7, rect.top + step1_10_y*3)};
        //	int npoints = 10;
        //	if( HasColorFill() )
        //	{
        //		if( IsSolidColorFill() )
        //			graphics.FillPolygon(&solidBrush, points, npoints);
        //		else
        //			graphics.FillPolygon(&lgBrush, points, npoints);
        //	}
        //	if( HasColorLine() )
        //	{
        //		graphics.DrawPolygon(&colorPen, points, npoints);
        //	}
        //}
        //else if( m_shapeType == ShapeType::parenthese_left )
        //{
        //	// * * * * * 1 * * * *
        //	// * 2 * * * * * * * *
        //	// * * * * * * * * * *
        //	// * 3 * * * * * * * *
        //	// 4 * * * * * * * * *
        //	// * 5 * * * * * * * *
        //	// * * * * * * * * * *
        //	// * 6 * * * * * * * *
        //	// * * * * * 7 * * *
        //	int step1_10_x = rect.Width() / 10;
        //	int step1_10_y = rect.Height() / 10;
        //	Point points[7] = {/*1*/ Point(rect.left + step1_10_x*5, rect.top), 
        //						/*2*/ Point(rect.left + step1_10_x*1, rect.top + step1_10_y*1), 
        //						/*3*/ Point(rect.left + step1_10_x*1, rect.top + step1_10_y*4), 
        //						/*4*/ Point(rect.left + step1_10_x*0, rect.top + step1_10_y*5), 
        //						/*5*/ Point(rect.left + step1_10_x*1, rect.top + step1_10_y*6), 							
        //						/*6*/ Point(rect.left + step1_10_x*1, rect.top + step1_10_y*9), 
        //						/*7*/ Point(rect.left + step1_10_x*5, rect.bottom /*top + step1_10_y*9*/)};
        //	int npoints = 7;
        //	graphics.DrawCurve(&colorPen, points, npoints);
        //}
        //else if( m_shapeType == ShapeType::parenthese_right )
        //{
        //	// * * * * 1 * * * * *
        //	// * * * * * * * * 2 *
        //	// * * * * * * * * * *
        //	// * * * * * * * * 3 *
        //	// * * * * * * * * * 4
        //	// * * * * * * * * 5 *
        //	// * * * * * * * * * *
        //	// * * * * * * * * 6 *
        //	// * * * * 7 * * * * *
        //	int step1_10_x = rect.Width() / 10;
        //	int step1_10_y = rect.Height() / 10;
        //	Point points[7] = {/*1*/ Point(rect.left + step1_10_x*5, rect.top), 
        //						/*2*/ Point(rect.left + step1_10_x*9, rect.top + step1_10_y*1), 
        //						/*3*/ Point(rect.left + step1_10_x*9, rect.top + step1_10_y*4), 
        //						/*4*/ Point(rect.right /*.left + step1_10_x*10*/, rect.top + step1_10_y*5), 
        //						/*5*/ Point(rect.left + step1_10_x*9, rect.top + step1_10_y*6), 							
        //						/*6*/ Point(rect.left + step1_10_x*9, rect.top + step1_10_y*9), 
        //						/*7*/ Point(rect.left + step1_10_x*5, rect.bottom /*top + step1_10_y*9*/)};
        //	int npoints = 7;
        //	graphics.DrawCurve(&colorPen, points, npoints);
        //}
        //else if( m_shapeType == ShapeType::ellipse )
        //{
        //	if( HasColorFill() )
        //	{
        //		if( IsSolidColorFill() )
        //			graphics.FillEllipse(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        //		else
        //			graphics.FillEllipse(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());
        //	}
        //	if( HasColorLine() )
        //	{
        //		graphics.DrawEllipse(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
        //	}
        //}
        //else
        {
            //if( IsSolidColorFill() )
            //	graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
            //else
            //	graphics.FillRectangle(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());

            //CString str;
            //str.Format("%s Shape type=%d", m_text.c_str(), m_shapeType);
            //// Font object
            //FontFamily fontFamily(L"Calibri");
            //Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
            //SolidBrush solidBrush(colorBlack);
            //graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
            //graphics.DrawString(CStringW(str), -1, &font, PointF(pointText.x, pointText.y), &solidBrush);
        }
    }

    //if( m_type == ElementType::type_shapes_infrastructure ||
    //		m_type == ElementType::type_image )
    //{
    //	if( m_image.IsEmpty() )
    //	{
    //		graphics.DrawRectangle(&penLine, rect.left, rect.top, rect.Width(), rect.Height());
    //		graphics.DrawLine(&penLine, p1.x, p1.y, p2.x, p2.y);
    //		graphics.DrawLine(&penLine, p1.x, p2.y, p2.x, p1.y);
    //	}
    //	else
    //	{			
    //		// Load the image		
    //		CStringW imageFilePath;
    //		
    //		// FIXME: Infrastructure shapes hard coded...
    //		if( m_type == ElementType::type_shapes_infrastructure )
    //			imageFilePath = GetImageFilePath();		
    //		if( m_type == ElementType::type_image )
    //			imageFilePath = GetImageFilePath();
    //		Image image(imageFilePath);
    //		//graphics.DrawImage(&image, rect.left, rect.top, rect.Width(), rect.Height());
    //		//graphics.DrawImage(&image, rect.left, rect.top, image.GetWidth(), image.GetHeight());

    //		if( m_type == ElementType::type_shapes_infrastructure )
    //		{
    //			graphics.DrawImage(&image, rect.left, rect.top, image.GetWidth(), image.GetHeight());
    //		}

    //		if( m_type == ElementType::type_image )
    //		{
    //			//Rect destRect(rect.left, rect.top, rect.Width(), rect.Height());
    //			//graphics.DrawImage(&image, destRect, 0, 0, image.GetWidth(), image.GetHeight(), UnitPixel, NULL, NULL, NULL);
    //			graphics.DrawImage(&image, rect.left, rect.top, image.GetWidth(), image.GetHeight());
    //		}
    //		
    //		// Infrastructure shapes are fixed size
    //		//if( m_type == type_shapes_infrastructure )
    //		{
    //			// Adjust fixed image size
    //			CPoint p1(rect.left, rect.top);
    //			CPoint p2(p1.x + image.GetWidth(), p1.y + image.GetHeight());
    //			m_rect.SetRect(p1, p2);		
    //		}

    //		// Useless or not to draw a rectangle around the image ???
    //		if( HasColorLine() )
    //		{
    //			rect = m_rect;
    //			graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    //		}

    //	}
    //}

    //if( m_type == ElementType::type_shapes_development )
    //{	
    //	if( m_shapeType == ShapeType::development_class )
    //	{
    //		graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    //	}
    //	if( m_shapeType == ShapeType::development_interface )
    //	{
    //		graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    //	}
    //	if( m_shapeType == ShapeType::development_enumeration )
    //	{
    //		graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    //	}
    //	if( m_shapeType == ShapeType::development_package )
    //	{
    //		int step1_4_x = rect.Width() / 4;

    //		// Draw little rectangle			
    //		graphics.FillRectangle(&solidBrush, rect.left, rect.top, step1_4_x*3, 30);
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, step1_4_x*3, 30);
    //		// Draw large rectangle
    //		graphics.FillRectangle(&solidBrush, rect.left, rect.top + 30, rect.Width(), rect.Height() - 30);
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top + 30, rect.Width(), rect.Height() - 30);
    //	}
    //	if( m_shapeType == ShapeType::development_comment )
    //	{
    //		graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    //		// Draw single line
    //		int width = rect.Width()-20; //*0.75;
    //		int height = 20; //Height()-20; //*0.25;
    //		graphics.DrawLine(&colorPen, rect.left + width, rect.top, rect.right, rect.top + height);
    //	}
    //	if( m_shapeType == ShapeType::development_component )
    //	{
    //		graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height()/2);
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    //		// middle fill
    //		graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height() /2);
    //	}
    //}


    //if( m_type == ElementType::type_text )
    //{
    //	//if( m_shapeType == ShapeType::text )
    //	{
    //		// Useless or not do fill a rectangle around the texte ???
    //		if( HasColorFill() )
    //		{
    //			if( IsSolidColorFill() )
    //				graphics.FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
    //			else
    //				graphics.FillRectangle(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());
    //		}
    //		// Useless or not to draw a rectangle around the text ???
    //		if( HasColorLine() )
    //		{
    //			graphics.DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    //		}

    //		// Font object
    //		FontFamily fontFamily(L"Calibri");
    //		Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
    //		// StringFormat object
    //		StringFormat stringFormat;
    //		if( m_shapeType == ShapeType::text_left )
    //		{
    //			stringFormat.SetAlignment(StringAlignmentNear);
    //		}
    //		if( m_shapeType == ShapeType::text_center )
    //		{
    //			stringFormat.SetAlignment(StringAlignmentCenter);
    //		}
    //		if( m_shapeType == ShapeType::text_right )
    //		{
    //			stringFormat.SetAlignment(StringAlignmentFar);
    //		}
    //		//stringFormat.SetLineAlignment(StringAlignmentCenter);
    //		// Brush object
    //		SolidBrush solidBrush(Color(255, 0, 0, 0));
    //		graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
    //		graphics.DrawString(CStringW(m_text), -1, &font, rectF, &stringFormat, &solidBrush);
    //	}
    //}
    //else
    {
        if (m_text.empty() == false)
        {
            //graphics.FillRectangle(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());

            // Font object
            FontFamily fontFamily(L"Calibri");
            Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
            SolidBrush solidBrush(Color(255, 0, 0, 0));
            graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
            graphics.DrawString(CStringW(m_text.c_str()), -1, &font, PointF(pointText.x, pointText.y), &solidBrush);
        }
    }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CxxxxElement
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// CLineElement class
//

//CLineElement::CLineElement()
//{
//}
//
//CLineElement::~CLineElement()
//{
//}

void CLineElement::Draw(CDrawingContext& ctxt)
{
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    CPoint& p1 = ctxt.GetTopLeft();
    CPoint& p2 = ctxt.GetBottomRight();

    if (m_shapeType == ShapeType::line || m_shapeType == ShapeType::line2)
    {
        graphics->DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);
    }
    else if (m_shapeType == ShapeType::line_right || m_shapeType == ShapeType::line_right2)
    {
        //colorPen.SetEndCap(LineCapArrowAnchor);
        //graphics->DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);

        //Create a Path, and add two lines to it.
        Point points[3] = { Point(-5, -5), Point(0, 0), Point(5, -5) };
        GraphicsPath capPath;
        capPath.AddLines(points, 3);

        // Create a CustomLineCap object.
        CustomLineCap custCap(NULL, &capPath);

        // Set the start and end caps for custCap.
        custCap.SetStrokeCap(LineCapTriangle);

        // Create a Pen object, assign startStrokeCap and endStrokeCap as the 
        // start and end caps, and draw a line.
        colorPen.SetCustomEndCap(&custCap);
        graphics->DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);
    }
    else if (m_shapeType == ShapeType::line_left_right)
    {
        colorPen.SetStartCap(LineCapArrowAnchor);
        colorPen.SetEndCap(LineCapArrowAnchor);
        graphics->DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);
    }
}

//
// CRectangleElement class
//
void CRectangleElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    if (HasColorFill())
    {
        if (IsSolidColorFill())
            graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        else
            graphics->FillRectangle(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());
    }
    if (HasColorLine())
    {
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    }
}

//
// CTriangleElement class
//
void CTriangleElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    Point points[3] = { Point(rect.left + rect.Width() / 2, rect.top),
                    Point(rect.right, rect.bottom),
                    Point(rect.left, rect.bottom) };
    if (HasColorFill())
    {
        if (IsSolidColorFill())
            graphics->FillPolygon(&solidBrush, points, 3);
        else
            graphics->FillPolygon(&lgBrush, points, 3);
    }
    if (HasColorLine())
    {
        graphics->DrawPolygon(&colorPen, points, 3);
    }
}

//
// CEllipseElement class
//
void CEllipseElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    if (HasColorFill())
    {
        if (IsSolidColorFill())
            graphics->FillEllipse(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        else
            graphics->FillEllipse(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());
    }
    if (HasColorLine())
    {
        graphics->DrawEllipse(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    }
}

//
// CArrowRightElement class
//
void CArrowRightElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    // * * * * 3 * * * * *
    // 1 - - - 2 * * * * *
    // - * * * * * * * * 4
    // 7 - - - 6 * * * * *
    // * * * * 5 * * * * *

    int step1_5_x = rect.Width() / 5;
    int step1_5_y = rect.Height() / 5;
    Point points[7] = { Point(rect.left, rect.top + step1_5_y),
                        Point(rect.left + step1_5_x * 3, rect.top + step1_5_y),
                        Point(rect.left + step1_5_x * 3, rect.top),
                        Point(rect.right, rect.top + rect.Height() / 2),
                        Point(rect.left + step1_5_x * 3, rect.bottom),
                        Point(rect.left + step1_5_x * 3, rect.bottom - step1_5_y),
                        Point(rect.left, rect.bottom - step1_5_y) };
    int npoints = 7;
    if (HasColorFill())
    {
        if (IsSolidColorFill())
            graphics->FillPolygon(&solidBrush, points, npoints);
        else
            graphics->FillPolygon(&lgBrush, points, npoints);
    }
    if (HasColorLine())
    {
        graphics->DrawPolygon(&colorPen, points, npoints);
    }
}

//
// CArrowDownElement class
//
void CArrowDownElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    // * * 1 * * * 2 * * *
    // * * * * * * * * * *
    // * * * * * * * * * *
    // * * * * * * * * * *
    // * * * * * * * * * *
    // 6 * 7 * * * 3 * * 4
    // * * * * * * * * * *
    // * * * * * * * * * *
    // * * * * * * * * * *
    // * * * * 5 * * * * *

    int step1_5_x = rect.Width() / 5;
    int step1_5_y = rect.Height() / 5;
    Point points[7] = {	/*1*/ Point(rect.left + step1_5_x * 1, rect.top),
        /*2*/ Point(rect.left + step1_5_x * 4, rect.top),
        /*3*/ Point(rect.left + step1_5_x * 4, rect.top + step1_5_y * 3),
        /*4*/ Point(rect.right, rect.top + step1_5_y * 3),
        /*5*/ Point(rect.left + rect.Width() / 2, rect.bottom),
        /*6*/ Point(rect.left, rect.top + step1_5_y * 3),
        /*7*/ Point(rect.left + step1_5_x * 1, rect.top + step1_5_y * 3) };

    int npoints = 7;
    if (HasColorFill())
    {
        if (IsSolidColorFill())
            graphics->FillPolygon(&solidBrush, points, npoints);
        else
            graphics->FillPolygon(&lgBrush, points, npoints);
    }
    if (HasColorLine())
    {
        graphics->DrawPolygon(&colorPen, points, npoints);
    }
}

//
// CStarElement class
//
void CStarElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    // * * * * 1 * * * * *
    // * * * * * * * * * *
    // 3 * 2 * * * *10 * 9
    // * * * * * * * * * *
    // * * 4 * * * * 8 * *
    // * * * * * * * * * *
    // * * * * 6 * * * * *
    // * * * * * * * * * *
    // * * * * * * * * * *
    // 5 * * * * * * * * 7

    int step1_10_x = rect.Width() / 10;
    int step1_10_y = rect.Height() / 10;
    Point points[10] = {/*1*/ Point(rect.left + rect.Width() / 2, rect.top),
        /*2*/ Point(rect.left + step1_10_x * 3, rect.top + step1_10_y * 3),
        /*3*/ Point(rect.left, rect.top + step1_10_y * 3),
        /*4*/ Point(rect.left + step1_10_x * 3, rect.top + step1_10_y * 5),
        /*5*/ Point(rect.left, rect.bottom),
        /*6*/ Point(rect.left + rect.Width() / 2, rect.top + step1_10_y * 7),
        /*7*/ Point(rect.right, rect.bottom),
        /*8*/ Point(rect.left + step1_10_x * 7, rect.top + step1_10_y * 5),
        /*9*/ Point(rect.right, rect.top + step1_10_y * 3),
        /*10*/Point(rect.left + step1_10_x * 7, rect.top + step1_10_y * 3) };
    int npoints = 10;
    if (HasColorFill())
    {
        if (IsSolidColorFill())
            graphics->FillPolygon(&solidBrush, points, npoints);
        else
            graphics->FillPolygon(&lgBrush, points, npoints);
    }
    if (HasColorLine())
    {
        graphics->DrawPolygon(&colorPen, points, npoints);
    }
}

//
// CParentheseLeftElement class
//
void CParentheseLeftElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    // * * * * * 1 * * * *
    // * 2 * * * * * * * *
    // * * * * * * * * * *
    // * 3 * * * * * * * *
    // 4 * * * * * * * * *
    // * 5 * * * * * * * *
    // * * * * * * * * * *
    // * 6 * * * * * * * *
    // * * * * * 7 * * *
    int step1_10_x = rect.Width() / 10;
    int step1_10_y = rect.Height() / 10;
    Point points[7] = {/*1*/ Point(rect.left + step1_10_x * 5, rect.top),
        /*2*/ Point(rect.left + step1_10_x * 1, rect.top + step1_10_y * 1),
        /*3*/ Point(rect.left + step1_10_x * 1, rect.top + step1_10_y * 4),
        /*4*/ Point(rect.left + step1_10_x * 0, rect.top + step1_10_y * 5),
        /*5*/ Point(rect.left + step1_10_x * 1, rect.top + step1_10_y * 6),
        /*6*/ Point(rect.left + step1_10_x * 1, rect.top + step1_10_y * 9),
        /*7*/ Point(rect.left + step1_10_x * 5, rect.bottom /*top + step1_10_y*9*/) };
    int npoints = 7;
    graphics->DrawCurve(&colorPen, points, npoints);
}

//
// CParentheseRightElement class
//
void CParentheseRightElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    // * * * * 1 * * * * *
    // * * * * * * * * 2 *
    // * * * * * * * * * *
    // * * * * * * * * 3 *
    // * * * * * * * * * 4
    // * * * * * * * * 5 *
    // * * * * * * * * * *
    // * * * * * * * * 6 *
    // * * * * 7 * * * * *
    int step1_10_x = rect.Width() / 10;
    int step1_10_y = rect.Height() / 10;
    Point points[7] = {/*1*/ Point(rect.left + step1_10_x * 5, rect.top),
        /*2*/ Point(rect.left + step1_10_x * 9, rect.top + step1_10_y * 1),
        /*3*/ Point(rect.left + step1_10_x * 9, rect.top + step1_10_y * 4),
        /*4*/ Point(rect.right /*.left + step1_10_x*10*/, rect.top + step1_10_y * 5),
        /*5*/ Point(rect.left + step1_10_x * 9, rect.top + step1_10_y * 6),
        /*6*/ Point(rect.left + step1_10_x * 9, rect.top + step1_10_y * 9),
        /*7*/ Point(rect.left + step1_10_x * 5, rect.bottom /*top + step1_10_y*9*/) };
    int npoints = 7;
    graphics->DrawCurve(&colorPen, points, npoints);
}

//
// CLineBrokenElement class
//
void CLineBrokenElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();

    if (m_shapeType == ShapeType::line_broken || m_shapeType == line_broken_right)
    {
        // 1 * * * 2 * * * * *
        // * * * * * * * * * *
        // * * * * * * * * * *
        // * * * * * * * * * *
        // * * * * 3 * * * * 4
        int step1_5_x = rect.Width() / 5;
        int step1_5_y = rect.Height() / 5;
        Point points[4] = { Point(rect.left, rect.top),
                            Point(rect.left + rect.Width() / 2, rect.top),
                            Point(rect.left + rect.Width() / 2, rect.bottom),
                            Point(rect.right, rect.bottom) };
        int npoints = 4;

        if (m_shapeType == line_broken_right)
        {
            //colorPen.SetEndCap(LineCapArrowAnchor);
            //Create a Path, and add two lines to it.
            Point points[3] = { Point(-5, -5), Point(0, 0), Point(5, -5) };
            GraphicsPath capPath;
            capPath.AddLines(points, 3);
            // Create a CustomLineCap object.
            CustomLineCap custCap(NULL, &capPath);
            // Set the start and end caps for custCap.
            custCap.SetStrokeCap(LineCapTriangle);
            // Create a Pen object, assign startStrokeCap and endStrokeCap as the 
            // start and end caps, and draw a line.
            colorPen.SetCustomEndCap(&custCap);
        }

        graphics->DrawLines(&colorPen, points, npoints);
    }
}

//
// CDevelopmentElement class
//
void CDevelopmentElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();

    if (m_shapeType == ShapeType::development_class)
    {
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    }
    if (m_shapeType == ShapeType::development_interface)
    {
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    }
    if (m_shapeType == ShapeType::development_enumeration)
    {
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
    }
    if (m_shapeType == ShapeType::development_package)
    {
        int step1_4_x = rect.Width() / 4;

        // Draw little rectangle			
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, step1_4_x * 3, 30);
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, step1_4_x * 3, 30);
        // Draw large rectangle
        graphics->FillRectangle(&solidBrush, rect.left, rect.top + 30, rect.Width(), rect.Height() - 30);
        graphics->DrawRectangle(&colorPen, rect.left, rect.top + 30, rect.Width(), rect.Height() - 30);
    }
    if (m_shapeType == ShapeType::development_comment)
    {
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
        // Draw single line
        int width = rect.Width() - 20; //*0.75;
        int height = 20; //Height()-20; //*0.25;
        graphics->DrawLine(&colorPen, rect.left + width, rect.top, rect.right, rect.top + height);
    }
    if (m_shapeType == ShapeType::development_component)
    {
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height() / 2);
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
        // middle fill
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height() / 2);
    }
}

//
// CImportElement class
//
void CImportElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    SolidBrush& solidBrushText = ctxt.GetBrushBlack();

    if (m_shapeType == ShapeType::import_class)
    {
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());

        CPoint& p1 = ctxt.GetTopLeft();
        CPoint& p2 = ctxt.GetBottomRight();
        CPoint pointText(rect.left + 10, rect.top + 10);

        // Font object
        FontFamily fontFamily(L"Calibri");
        Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
        graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);

        //m_text = this->m_TypeData->m_Name;
        graphics->DrawString(CStringW(this->m_text.c_str()), -1, &font, PointF(pointText.x, pointText.y), &solidBrushText);

        if (this->m_TypeData == nullptr)
        {
            return;
        }

        int count = 2; // class name is entry 1 and was done see previous...
        for (auto it = this->m_TypeData->m_Properties.begin(); it != this->m_TypeData->m_Properties.end(); it++)
        {
            std::shared_ptr<CPropertyData> ppd = *it;
            std::wstring propertyName = ppd->m_Name;
            std::wstring propertyType = ppd->m_Type;
            std::wstringstream str1;
            str1 << propertyType << L" " << propertyName;

            CPoint pointText2(rect.left + 10, rect.top + count * 10);

            //graphics->DrawString(CStringW(propertyName.c_str()), -1, &font, PointF(pointText2.x, pointText2.y), &solidBrushText);
            graphics->DrawString(CStringW(str1.str().c_str()), -1, &font, PointF(pointText2.x, pointText2.y), &solidBrushText);

            count++;
        }

        for (auto it = this->m_TypeData->m_Methods.begin(); it != this->m_TypeData->m_Methods.end(); it++)
        {
            std::shared_ptr<CMethodData> pmd = *it;
            std::wstring methodName = pmd->m_Name;

            CPoint pointText2(rect.left + 10, rect.top + count * 10);

            graphics->DrawString(CStringW(methodName.c_str()), -1, &font, PointF(pointText2.x, pointText2.y), &solidBrushText);

            count++;
        }

        for (auto it = this->m_TypeData->m_Fields.begin(); it != this->m_TypeData->m_Fields.end(); it++)
        {
            std::shared_ptr<CFieldData> pfd = *it;
            std::wstring fieldName = pfd->m_Name;
            std::wstring fieldType = pfd->m_Type;
            std::wstringstream str1;
            str1 << fieldType << L" " << fieldName;

            CPoint pointText2(rect.left + 10, rect.top + count * 10);

            //graphics->DrawString(CStringW(fieldName.c_str()), -1, &font, PointF(pointText2.x, pointText2.y), &solidBrushText);
            graphics->DrawString(CStringW(str1.str().c_str()), -1, &font, PointF(pointText2.x, pointText2.y), &solidBrushText);

            count++;
        }
    }
}
 
//
// CStartMenuElement class
//
void CStartMenuElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    SolidBrush& solidBrushText = ctxt.GetBrushWhite();

    if (m_shapeType == ShapeType::start_menu_element)
    {
        Color gdiColorFill(255, 0, 0, 0);
        SolidBrush gdiBrushColor(gdiColorFill);
        gdiColorFill.SetValue(Color::MakeARGB(255, rand() % 255, rand() % 255, rand() % 255));
        gdiBrushColor.SetColor(gdiColorFill);

        //graphics->FillRectangle(&gdiBrushColor, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());

        // Font object
        FontFamily fontFamily(L"Calibri");
        Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
        graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);

        StringFormat stringFormat;
        stringFormat.SetAlignment(StringAlignment::StringAlignmentCenter);
        stringFormat.SetLineAlignment(StringAlignment::StringAlignmentCenter);

        m_text = m_attr.m_Name;

        RectF rectF(rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawString(CStringW(this->m_text.c_str()), -1, &font, rectF, &stringFormat, &solidBrushText);
        //CPoint pointText(rect.left + 10, rect.top + 10);
        //graphics->DrawString(CStringW(this->m_text.c_str()), -1, &font, PointF(pointText.x, pointText.y), &solidBrushText);
    }
}

//
// CImageElement class
//
void CImageElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    CPoint& p1 = ctxt.GetTopLeft();
    CPoint& p2 = ctxt.GetBottomRight();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();

    if (m_image.length() == 0)
    {
        graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
        graphics->DrawLine(&colorPen, p1.x, p1.y, p2.x, p2.y);
        graphics->DrawLine(&colorPen, p1.x, p2.y, p2.x, p1.y);
    }
    else
    {
        // Load the image		
        std::wstring imageFilePath;

        // FIXME: Infrastructure shapes hard coded...
        if (m_type == ElementType::type_shapes_infrastructure)
            imageFilePath = GetImageFilePath();
        if (m_type == ElementType::type_image)
            imageFilePath = GetImageFilePath();
        Image image(CStringW(imageFilePath.c_str()));
        //graphics->DrawImage(&image, rect.left, rect.top, rect.Width(), rect.Height());
        //graphics->DrawImage(&image, rect.left, rect.top, image.GetWidth(), image.GetHeight());

        if (m_type == ElementType::type_shapes_infrastructure)
        {
            graphics->DrawImage(&image, rect.left, rect.top, image.GetWidth(), image.GetHeight());
        }

        if (m_type == ElementType::type_image)
        {
            //Rect destRect(rect.left, rect.top, rect.Width(), rect.Height());
            //graphics->DrawImage(&image, destRect, 0, 0, image.GetWidth(), image.GetHeight(), UnitPixel, NULL, NULL, NULL);
            graphics->DrawImage(&image, rect.left, rect.top, image.GetWidth(), image.GetHeight());
        }

        // Infrastructure shapes are fixed size
        //if( m_type == type_shapes_infrastructure )
        {
            // Adjust fixed image size
            CPoint p1(rect.left, rect.top);
            CPoint p2(p1.x + image.GetWidth(), p1.y + image.GetHeight());
            m_rect.SetRect(p1, p2);
        }

        // Useless or not to draw a rectangle around the image ???
        if (HasColorLine())
        {
            rect = m_rect;
            graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
        }

    }
}

//
// CInfrastructureElement class
//
void CInfrastructureElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    SolidBrush& solidBrush = ctxt.GetBrushColor();

}

//
// CTextElement class
//
void CTextElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    CPoint& p1 = ctxt.GetTopLeft();
    CPoint& p2 = ctxt.GetBottomRight();
    SolidBrush& solidBrush = ctxt.GetBrushColor();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();
    // RectF object for Text
    PointF pointF(p1.x, p1.y);
    SizeF sizeF(rect.Width(), rect.Height());
    RectF rectF(pointF, sizeF);

    //if( m_shapeType == ShapeType::text )
    {
        // Useless or not do fill a rectangle around the texte ???
        if (HasColorFill())
        {
            if (IsSolidColorFill())
                graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
            else
                graphics->FillRectangle(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());
        }
        // Useless or not to draw a rectangle around the text ???
        if (HasColorLine())
        {
            graphics->DrawRectangle(&colorPen, rect.left, rect.top, rect.Width(), rect.Height());
        }

        // Font object
        //FontFamily fontFamily(L"Calibri");
        //Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
        CStringW fontName(m_fontName.c_str());
        FontFamily fontFamily(fontName);
        Gdiplus::Font font(&fontFamily, this->m_fontSize, FontStyleRegular, UnitPixel);
        // StringFormat object
        StringFormat stringFormat;
        if (m_shapeType == ShapeType::text_left)
        {
            stringFormat.SetAlignment(StringAlignmentNear);
        }
        if (m_shapeType == ShapeType::text_center)
        {
            stringFormat.SetAlignment(StringAlignmentCenter);
        }
        if (m_shapeType == ShapeType::text_right)
        {
            stringFormat.SetAlignment(StringAlignmentFar);
        }
        //stringFormat.SetLineAlignment(StringAlignmentCenter);
        // Brush object
        SolidBrush solidBrush(Color(255, 0, 0, 0));
        graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
        graphics->DrawString(CStringW(m_text.c_str()), -1, &font, rectF, &stringFormat, &solidBrush);
    }
}

void CSimpleTextElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    CPoint& p1 = ctxt.GetTopLeft();
    CPoint& p2 = ctxt.GetBottomRight();
    SolidBrush& solidBrush = ctxt.GetBrushBlack();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();
    CPoint pointText(rect.left + 10, rect.top + 10);

    if (m_text.empty() == false)
    {
        // Font object
        FontFamily fontFamily(L"Calibri");
        Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
        graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
        graphics->DrawString(CStringW(m_text.c_str()), -1, &font, PointF(pointText.x, pointText.y), &solidBrush);
    }

}

//
// CNotImplementedElement class
//
void CNotImplementedElement::Draw(CDrawingContext& ctxt)
{
    CRect rect = m_rect;
    Graphics* graphics = ctxt.GetGraphics();
    Pen& colorPen = ctxt.GetPenColor();
    CPoint& p1 = ctxt.GetTopLeft();
    CPoint& p2 = ctxt.GetBottomRight();
    SolidBrush& solidBrush = ctxt.GetBrushBlack();
    LinearGradientBrush& lgBrush = ctxt.GetGradientBrushColor();
    CPoint pointText(rect.left + 10, rect.top + 10);

    if (IsSolidColorFill())
        graphics->FillRectangle(&solidBrush, rect.left, rect.top, rect.Width(), rect.Height());
    else
        graphics->FillRectangle(&lgBrush, rect.left, rect.top, rect.Width(), rect.Height());

    CString str;
    str.Format(_T("%s Shape type=%d"), m_text.c_str(), m_shapeType);
    // Font object
    FontFamily fontFamily(L"Calibri");
    Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);
    graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
    graphics->DrawString(CStringW(str), -1, &font, PointF(pointText.x, pointText.y), &solidBrush);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CElementContainer Class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CElementContainer, CObject, 0)

CElementContainer::CElementContainer()
{
    //m_objects.reserve(1000);
}

CElementContainer::~CElementContainer(void)
{
}

void CElementContainer::Serialize(CElementManager* pElementManager, CArchive& ar)
{
    if (ar.IsStoring() == TRUE)
    {
        CTypedPtrList<CObList, CElement*> objects;
        for (vector<std::shared_ptr<CElement>>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
        {
            std::shared_ptr<CElement> pElement = *i;
            objects.AddTail(pElement.get());
        }

        objects.Serialize(ar);
    }
    else
    {
        CTypedPtrList<CObList, CElement*> objects;
        objects.Serialize(ar);

        POSITION pos = objects.GetHeadPosition();
        while (pos != NULL)
        {
            CElement* pElement = objects.GetNext(pos);
            //std::shared_ptr<CElement> pNewElement(pElement);

            //FIXED 14July2012 05:30PM
            std::shared_ptr<CElement> pNewElement = CFactory::CreateElementOfType(pElement->m_type, pElement->m_shapeType);
            pNewElement->m_name = pElement->m_name;
            pNewElement->m_text = pElement->m_text;
            pNewElement->m_objectId = pElement->m_objectId;
            pNewElement->m_rect = pElement->m_rect;
            pNewElement->m_bColorFill = pElement->m_bColorFill;
            pNewElement->m_bColorLine = pElement->m_bColorLine;
            pNewElement->m_bColorFill = pElement->m_bColorFill;
            pNewElement->m_bLineWidth = pElement->m_bLineWidth;
            pNewElement->m_bSolidColorFill = pElement->m_bSolidColorFill;
            //pNewElement->m_caption = pElement->m_caption;
            pNewElement->m_colorFill = pElement->m_colorFill;
            pNewElement->m_colorLine = pElement->m_colorLine;
            pNewElement->m_image = pElement->m_image;
            pNewElement->m_last = pElement->m_last;
            pNewElement->m_lineWidth = pElement->m_lineWidth;
            pNewElement->m_pManager = pElementManager; // TODO
            pNewElement->m_point = pElement->m_point;
            POSITION pos = /*pNewElement->m_pView =*/ ar.m_pDocument->GetFirstViewPosition(); //nullptr; // TODO
            pNewElement->m_pView = (CStartMenuViewEx*)(ar.m_pDocument->GetNextView(pos)); //()->GetRoutingView();
            m_objects.push_back(pNewElement);
        }
    }

}

std::shared_ptr<CElement> CElementContainer::FindElement(ElementType type)
{
    // find last element of a given type (m_type)
    for (vector<std::shared_ptr<CElement>>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        if (pElement->m_type == type)
        {
            return pElement;
        }
    }
    std::shared_ptr<CElement> pNull;
    return pNull;
}

std::shared_ptr<CElement> CElementContainer::FindElement(std::wstring objectId)
{
    // find last element of a given type
    for (vector<std::shared_ptr<CElement>>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        if (pElement->m_objectId == objectId)
        {
            return pElement;
        }
    }
    std::shared_ptr<CElement> pNull;
    return pNull;
}

bool CElementContainer::FindElement(std::wstring objectId, vector<std::shared_ptr<CElement>>::iterator& it)
{
    // find last element of a given type
    for (vector<std::shared_ptr<CElement>>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        if (pElement->m_objectId == objectId)
        {
            it = i;
            return true;
        }
    }
    return false;
}

std::shared_ptr<CElement> CElementContainer::ObjectAt(const CPoint& point)
{
    CRect rect(point, CSize(1, 1));
    for (vector<std::shared_ptr<CElement>>::reverse_iterator i = m_objects.rbegin(); i != m_objects.rend(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        if (pElement->Intersects(rect))
        {
            return pElement;
        }
    }
    std::shared_ptr<CElement> pNull;
    return pNull;
}

std::shared_ptr<CElement> CElementContainer::GetHead()
{
    vector<std::shared_ptr<CElement>>::iterator i = m_objects.begin();
    if (i != m_objects.end())
    {
        std::shared_ptr<CElement> pElement = *i;
        return pElement;
    }

    std::shared_ptr<CElement> pNull;
    return pNull;
}

int CElementContainer::GetCount()
{
    int count = m_objects.size();
    return count;
}


void CElementContainer::MoveToFront(const CElementContainer& selection)
{
    /*
    POSITION pos = selection.m_objects.GetHeadPosition();
    while (pos != NULL)
    {
        CElement * pElement = selection.m_objects.GetNext(pos);
        POSITION posObjects = m_objects.Find(pElement);
        if( posObjects != NULL )
        {
            m_objects.RemoveAt(posObjects);
            m_objects.AddTail(pElement);
        }
    }
    */
    // MSVC STL no problem
    //for( auto itSel = selection.m_objects.begin() ; itSel!=selection.m_objects.end() ; itSel++ )
    // Boost stl need a const_iterator...
    //for( auto itSel = selection.m_objects.begin() ; itSel!=selection.m_objects.end() ; itSel++ )
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        vector<std::shared_ptr<CElement>>::iterator pos = find(m_objects.begin(), m_objects.end(), pElement);
        if (pos != m_objects.end())
        {
            m_objects.erase(pos);
            m_objects.push_back(pElement);
        }
    }
}

void CElementContainer::MoveToBack(const CElementContainer& selection)
{
    /*
    POSITION pos = selection.m_objects.GetHeadPosition();
    while (pos != NULL)
    {
        CElement * pElement = selection.m_objects.GetNext(pos);
        POSITION posObjects = m_objects.Find(pElement);
        if( posObjects != NULL )
        {
            m_objects.RemoveAt(posObjects);
            m_objects.AddHead(pElement);
        }
    }
    */
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        vector<std::shared_ptr<CElement>>::iterator pos = find(m_objects.begin(), m_objects.end(), pElement);
        if (pos != m_objects.end())
        {
            m_objects.erase(pos);
            m_objects.insert(m_objects.begin(), pElement);
        }
    }
}

void CElementContainer::MoveForward(const CElementContainer& selection)
{
    /*
    POSITION pos = selection.m_objects.GetHeadPosition();
    while (pos != NULL)
    {
        CElement * pElement = selection.m_objects.GetNext(pos);
        POSITION posObjects = m_objects.Find(pElement);
        if( posObjects != NULL )
        {
            if (posObjects != m_objects.GetTailPosition())
            {
                POSITION posNext = posObjects;
                m_objects.GetNext(posNext);
                m_objects.RemoveAt(posObjects);
                m_objects.InsertAfter(posNext, pElement);
            }
        }
    }
    */
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        vector<std::shared_ptr<CElement>>::iterator pos = find(m_objects.begin(), m_objects.end(), pElement);
        if (pos != m_objects.end())
        {
            std::shared_ptr<CElement>& pLastElement = m_objects.back();
            if (pElement != pLastElement)
            {
                m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), pElement), m_objects.end());
                m_objects.insert(pos + 1, pElement);
            }
        }
    }
}

void CElementContainer::MoveBackward(const CElementContainer& selection)
{
    /*
    POSITION pos = selection.m_objects.GetHeadPosition();
    while (pos != NULL)
    {
        CElement * pElement = selection.m_objects.GetNext(pos);
        POSITION posObjects = m_objects.Find(pElement);
        if( posObjects != NULL )
        {
            if (posObjects != m_objects.GetHeadPosition())
            {
                POSITION posNext = posObjects;
                m_objects.GetPrev(posNext);
                m_objects.RemoveAt(posObjects);
                m_objects.InsertBefore(posNext, pElement);
            }
        }
    }
    */
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        vector<std::shared_ptr<CElement>>::iterator pos = find(m_objects.begin(), m_objects.end(), pElement);
        if (pos != m_objects.end())
        {
            std::shared_ptr<CElement>& pFirstElement = m_objects.front();
            if (pElement != pFirstElement)
            {
                pos--;
                m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), pElement), m_objects.end());
                m_objects.insert(pos, pElement);
            }
        }
    }
}

void CElementContainer::Remove(const CElementContainer& selection)
{
    //POSITION pos = selection.m_objects.GetHeadPosition();
    //while (pos != NULL)
    //{
    //	CElement * pElement = selection.m_objects.GetNext(pos);
    //	POSITION posObjects = m_objects.Find(pElement);
    //	if( posObjects != NULL )
    //	{
    //		m_objects.RemoveAt(posObjects);
    //	}
    //}

    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;

        vector<std::shared_ptr<CElement>>::iterator pos;
        pos = find(m_objects.begin(), m_objects.end(), pElement);
        if (pos != m_objects.end())
        {
            m_objects.erase(pos);
        }
    }
}

void CElementContainer::Copy(const CElementContainer& selection)
{
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        m_objects.push_back(pElement);
    }
}

void CElementContainer::Clone(const CElementContainer& selection)
{
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        std::shared_ptr<CElement> pNewElement = pElement->MakeCopy();
        pNewElement->SetGuid();
        pNewElement->SetName();
        m_objects.push_back(pNewElement);
    }
}

void CElementContainer::CopyWithAttributesChange(const CElementContainer& selection)
{
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = selection.m_objects.begin(); itSel != selection.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        pElement->SetName();
        pElement->SetGuid();
        m_objects.push_back(pElement);
    }

}

void CElementContainer::ChangeInnerAttributes()
{
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = m_objects.begin(); itSel != m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        pElement->SetName();
        pElement->SetGuid();
    }
}

void CElementContainer::RemoveAll()
{
    m_objects.clear();
}

void CElementContainer::Remove(std::shared_ptr<CElement> pElement)
{
    for (vector<std::shared_ptr<CElement>>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
    {
        std::shared_ptr<CElement> pObj = *i;
        if (pObj->m_objectId == pElement->m_objectId)
        {
            m_objects.erase(i);
            break;
            //delete pObj;
        }
    }
}

void CElementContainer::AddTail(std::shared_ptr<CElement> pElement)
{
    m_objects.push_back(pElement);
}

void CElementContainer::DebugDumpObjects(CStartMenuViewEx* pView)
{
    CString str;
    for (vector<std::shared_ptr<CElement>>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        str.Format(_T("dump %s"), pElement->ToString());
        pView->LogDebug(str);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CElementManager
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CElementManager, CObject, 0)

CElementManager::CElementManager()
{
    m_objectId = L"";
    m_lastPoint = CPoint(0, 0);
    m_paperColor = RGB(255, 255, 255); //RGB(242, 242, 200); //RGB(255, 255, 255); //RGB(188, 251, 255);
    m_size = CSize(2500, 2500);

    // Initialize Current UI interaction members
    m_bDrawing = FALSE;
    // Current selected drawing tool = SELECT
    m_type = ElementType::type_select;
    // Current selected shape type from Ribbon = type_unknown
    m_shapeType = ShapeType::unknown;
    m_nDragHandle = 1;
    m_fZoomFactor = 1.0f;

    // Initiate the connection with the Property Window
    ConnectToPropertyGrid();
}

void CElementManager::ConnectToPropertyGrid()
{
    CWnd* p = AfxGetMainWnd();
    CMainFrame* pmf = (CMainFrame*)p;
    //pmf->SetManager(this);
}

CElementManager::~CElementManager(void)
{
}

void CElementManager::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_size;
        ar << m_paperColor;
        ar << m_lastPoint;
    }
    else
    {
        ar >> m_size;
        ar >> m_paperColor;
        ar >> m_lastPoint;
    }

    m_objects.Serialize(this, ar);
}

void CElementManager::RemoveSelectedObjects(CStartMenuViewEx* pView)
{
    m_objects.Remove(m_selection);
    SelectNone();

    // Update ClassView & FileView
    UpdateClassView();//pNewElement);
    UpdateFileView();//pNewElement);

    Invalidate(pView);
}

void CElementManager::OnFont(CStartMenuViewEx* pView)
{
}

void CElementManager::OnFontSize(CStartMenuViewEx* pView)
{
}

void CElementManager::OnEditCut(CStartMenuViewEx* pView)
{
    // the clipboard is cleared
    m_clipboard.RemoveAll();
    // the current selection is cleared
    RemoveSelectedObjects(pView);
}

void CElementManager::OnEditCopy(CStartMenuViewEx* pView)
{
    m_clipboard.RemoveAll();
    //m_selection.ChangeInnerAttributes();
    m_clipboard.Clone(m_selection);
    //m_clipboard.ChangeInnerAttributes();
}

void CElementManager::OnEditPaste(CStartMenuViewEx* pView)
{
    m_objects.Clone(m_clipboard);
    for (vector<std::shared_ptr<CElement>>::const_iterator itSel = m_clipboard.m_objects.begin(); itSel != m_clipboard.m_objects.end(); itSel++)
    {
        std::shared_ptr<CElement> pElement = *itSel;
        Select(pElement);
    }
    m_selectMode = SelectMode::move;

    m_clipboard.RemoveAll();

    Invalidate(pView);
}

void CElementManager::MoveToFront(CStartMenuViewEx* pView)
{
    m_objects.MoveToFront(m_selection);
    Invalidate(pView);
}

void CElementManager::MoveForward(CStartMenuViewEx* pView)
{
    m_objects.MoveForward(m_selection);
    Invalidate(pView);
}

void CElementManager::MoveBackward(CStartMenuViewEx* pView)
{
    m_objects.MoveBackward(m_selection);
    Invalidate(pView);
}

void CElementManager::MoveToBack(CStartMenuViewEx* pView)
{
    m_objects.MoveToBack(m_selection);
    Invalidate(pView);
}

bool CElementManager::HasSelection()
{
    if (m_selection.GetCount() > 0)
        return true;
    else
        return false;
}

bool CElementManager::IsSelected(std::shared_ptr<CElement> pElement)
{
    std::shared_ptr<CElement> ptr = m_selection.FindElement(pElement->m_objectId);
    if (ptr != nullptr)
        return true;
    else
        return false;
}

void CElementManager::SelectNone()
{
    m_selection.RemoveAll();
}

bool CElementManager::Select(std::shared_ptr<CElement> pElement)
{
    m_selection.AddTail(pElement);
    return true;
}

bool CElementManager::Deselect(std::shared_ptr<CElement> pElement)
{
    m_selection.Remove(pElement);
    return true;
}

void CElementManager::ViewToManager(CStartMenuViewEx* pView, CPoint& point)
{
    // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
    //CClientDC dc(pView);
    //pView->OnPrepareDC(&dc, NULL);
    //dc.DPtoLP(&point);

    CString str;
    CPoint scrollPoint = pView->GetScrollPosition();
    str.Format(_T("scroll point {%d,%d}"), scrollPoint.x, scrollPoint.y);
    //pView->LogDebug(str);

    point.operator+=(scrollPoint);

    CClientDC dc(pView);
    Graphics graphics(dc.m_hDC);
    graphics.ScaleTransform(m_fZoomFactor, m_fZoomFactor);
    Point points[1] = { Point(point.x, point.y) };
    // Transform the points in the array from world to page coordinates.
    graphics.TransformPoints(
        CoordinateSpaceWorld,
        CoordinateSpaceDevice,
        points,
        1);
    point.x = points[0].X;
    point.y = points[0].Y;
}

void CElementManager::ViewToManager(CStartMenuViewEx* pView, CRect& rect)
{
    // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
    //CClientDC dc(pView);
    //pView->OnPrepareDC(&dc, NULL);
    //dc.DPtoLP(&rect);

    CClientDC dc(pView);
    Graphics graphics(dc.m_hDC);
    graphics.ScaleTransform(m_fZoomFactor, m_fZoomFactor);
    CPoint point1 = rect.TopLeft();
    CPoint point2 = rect.BottomRight();
    Point points[2] = { Point((int)point1.x, (int)point1.y),
                        Point((int)point2.x, (int)point2.y) };
    // Transform the points in the array from world to page coordinates.
    graphics.TransformPoints(
        CoordinateSpaceWorld,
        CoordinateSpaceDevice,
        points,
        2);

    point1.x = points[0].X;
    point1.y = points[0].Y;
    point2.x = points[1].X;
    point2.y = points[1].Y;
    rect.SetRect(point1, point2);
}

void CElementManager::ManagerToView(CStartMenuViewEx* pView, CPoint& point)
{
    //CClientDC dc(pView);
    //pView->OnPrepareDC(&dc, NULL);
    //dc.LPtoDP(&point);

    CClientDC dc(pView);
    Graphics graphics(dc.m_hDC);
    graphics.ScaleTransform(m_fZoomFactor, m_fZoomFactor);
    Point points[1] = { Point(point.x, point.y) };
    // Transform the points in the array from world to page coordinates.
    graphics.TransformPoints(
        CoordinateSpaceDevice,
        CoordinateSpaceWorld,
        points,
        1);
    point.x = points[0].X;
    point.y = points[0].Y;
}

void CElementManager::ManagerToView(CStartMenuViewEx* pView, CRect& rect)
{
    //CClientDC dc(pView);
    //pView->OnPrepareDC(&dc, NULL);
    //dc.LPtoDP(&rect);

    CClientDC dc(pView);
    Graphics graphics(dc.m_hDC);
    graphics.ScaleTransform(m_fZoomFactor, m_fZoomFactor);
    CPoint point1 = rect.TopLeft();
    CPoint point2 = rect.BottomRight();
    Point points[2] = { Point((int)point1.x, (int)point1.y),
                        Point((int)point2.x, (int)point2.y) };
    // Transform the points in the array from world to page coordinates.
    graphics.TransformPoints(
        CoordinateSpaceDevice,
        CoordinateSpaceWorld,
        points,
        2);

    point1.x = points[0].X;
    point1.y = points[0].Y;
    point2.x = points[1].X;
    point2.y = points[1].Y;
    rect.SetRect(point1, point2);
}

void CElementManager::PrepareDC(CStartMenuViewEx* pView, CDC* pDC, CPrintInfo* pInfo)
{
    return;

    // mapping mode is MM_ANISOTROPIC
    // these extents setup a mode similar to MM_LOENGLISH
    // MM_LOENGLISH is in .01 physical inches
    // these extents provide .01 logical inches

    CSize size = GetSize();

    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetViewportExt(size.cx, size.cy);
    pDC->SetWindowExt(size.cx, size.cy);

    // set the origin of the coordinate system to the center of the page
    CPoint ptOrg;
    ptOrg.x = 0; //GetDocument()->GetSize().cx / 2;
    ptOrg.y = 0; //GetDocument()->GetSize().cy / 2;

    // ptOrg is in logical coordinates
    pDC->OffsetWindowOrg(0, 0); //-ptOrg.x,ptOrg.y);
}

void CElementManager::DrawBackground(CStartMenuViewEx* pView, CDC* pDC)
{
    Graphics graphics(pDC->m_hDC);
    CSize size = GetSize();
    //SolidBrush brush(Color(255, 255, 255, 255));
    Color colorLine(255, GetRValue(GetPaperColor()), GetGValue(GetPaperColor()), GetBValue(GetPaperColor()));
    SolidBrush brush(colorLine);
    Rect fillRect(0, 0, size.cx, size.cy);
    graphics.FillRectangle(&brush, fillRect);
}

void CElementManager::Draw(CStartMenuViewEx* pView, CDC* pDC)
{
    // Initialize GDI+ graphics context
    Graphics graphics(pDC->m_hDC);
    // just like that
    //graphics.ScaleTransform(0.75f, 0.75f);
    graphics.ScaleTransform(m_fZoomFactor, m_fZoomFactor);

    // TODO: add draw code for native data here
    for (vector<std::shared_ptr<CElement>>::const_iterator i = GetObjects().begin(); i != GetObjects().end(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        // FIXME: Update the view for Property Window
        pElement->m_pView = pView;

        // Construct the graphic context for each element
        CDrawingContext ctxt(pElement);
        ctxt.m_pGraphics = &graphics;

        //pElement->Draw(pView, pDC);
        pElement->Draw(ctxt);

        // HACK 14072012 : no more SimpleTextElement / Just other text elements except for caption old element
        // caption property is deprecated. be carefull. DO NOT USE m_caption any more !!!
        // informations: 
        //    for m_type that are simple shapes  ; it means it is not about text shapes,
        //    the m_text property can be optional and if it exists,
        //    it should be appended to the rendering area by creating a dedicated object. 
        //    We call it CSimpleTextElement.
        //if (pElement->m_text.empty() == false &&
        //    (pElement->m_type != ElementType::type_text)
        //    )
        //{
        //    //std::shared_ptr<CElement> pTextElement = make_shared<CSimpleTextElement>();
        //    std::shared_ptr<CElement> pTextElement(new CSimpleTextElement());
        //    pTextElement->m_rect = pElement->m_rect;
        //    pTextElement->m_text = pElement->m_text;
        //    pTextElement->Draw(ctxt);
        //}

        //if( !pDC->IsPrinting() && IsSelected(pObj) )
        //	DrawTracker(pObj, pDC, TrackerState::selected);
        if (pView != NULL && pView->m_bActive && !pDC->IsPrinting() && IsSelected(pElement))
            pElement->DrawTracker(ctxt, TrackerState::selected);
    }
}

void CElementManager::DrawEx(CStartMenuViewEx* pView, CDC* pDC)
{
    CDC dc;
    CDC* pDrawDC = pDC;
    CBitmap bitmap;
    CBitmap* pOldBitmap = nullptr;

    // only paint the rect that needs repainting
    CRect client;
    CSize size = GetSize();
    CRect fillRect(0, 0, size.cx, size.cy);

    // version n°1
    // Previous : it was working since Ribbon UI...
    //pDC->GetClipBox(client);
    //ManagerToView(pView, rect);

    // version n°2
    // HACK?
    //pView->GetClientRect(client);

    // version n°3
    client = fillRect;

    CRect rect = client;
    //rect.NormalizeRect();

    //CString str;
    //str.Format(_T("client=%d,%d,%d,%d"), client.left, client.top, client.right, client.bottom);
    //pView->LogDebug(str);

    if (!pDC->IsPrinting())
    {
        // draw to offscreen bitmap for fast looking repaints
        if (dc.CreateCompatibleDC(pDC))
        {
            if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
            {
                pView->OnPrepareDC(&dc, NULL);
                pDrawDC = &dc;

                // offset origin more because bitmap is just piece of the whole drawing
                dc.OffsetViewportOrg(rect.left, rect.top);
                pOldBitmap = dc.SelectObject(&bitmap);
                //dc.SetBrushOrg(rect.left % 8, rect.top % 8);

                // might as well clip to the same rectangle
                dc.IntersectClipRect(client);
            }
        }
    }

#ifdef DRAW_PAPER_BACKGROUND
    // paint background
    CBrush brush;
    if (!brush.CreateSolidBrush(GetPaperColor()))
        return;
    brush.UnrealizeObject();

    //CSize size = GetSize();
    //CRect fillRect(0, 0 , size.cx, size.cy);
    pDrawDC->FillRect(fillRect, &brush);
    //pDrawDC->FillRect(client, &brush);

    //if (!pDC->IsPrinting() && m_bGrid)
    //	DrawGrid(pDrawDC);
#endif

    // Background drawing routine call
    DrawBackground(pView, pDrawDC);

    // Main drawing routine call
    Draw(pView, pDrawDC);

    if (pDrawDC != pDC)
    {
        pDC->SetViewportOrg(0, 0);
        pDC->SetWindowOrg(0, 0);
        pDC->SetMapMode(MM_TEXT);
        dc.SetViewportOrg(0, 0);
        dc.SetWindowOrg(0, 0);
        dc.SetMapMode(MM_TEXT);
        pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
        dc.SelectObject(pOldBitmap);
    }

    // Caution, it flicks !
    //pView->LogDebug(_T("CElementManager::DrawEx"));
}

void CElementManager::OnLButtonDown(CStartMenuViewEx* pView, UINT nFlags, const CPoint& cpoint)
{
    // Caution, it flicks !
    //pView->LogDebug(_T("CElementManager::OnLButtonDown"));

    if (m_type == ElementType::type_unknown)
    {
        //FIXME : do we need to handle not implemented objects ?
        return;
    }

    //m_bDrawing = true;

    CPoint point = cpoint;
    ViewToManager(pView, point);
    m_lastPoint = point;

    // Debugging
    CString str;
    str.Format(_T("point {%d,%d} / {%d,%d}"), cpoint.x, cpoint.y, point.x, point.y);
    pView->LogDebug(str);

    if (m_type == ElementType::type_select)
    {

        m_selectMode = SelectMode::none;

        // Check for resizing (only allowed on single selections)
        if (HasSelection() && m_selection.GetCount() == 1)
        {
            std::shared_ptr<CElement> pElement = m_selection.GetHead();
            // Change cursor look because mouse click is over an object for sizing 
            m_nDragHandle = pElement->HitTest(point, pView, TRUE);
            if (m_nDragHandle != 0)
            {
                m_selectMode = SelectMode::size;
                pView->LogDebug(_T("selectMode == sized"));
            }
        }

        if (m_selectMode == SelectMode::none)
        {
            // See if the click was on an object
            std::shared_ptr<CElement> pElement = m_objects.ObjectAt(point);
            if (pElement != NULL)
            {
                //if( HasSelection() )
                //{
                //	pView->LogDebug("selection cleared");
                //	SelectNone();
                //}

                pView->LogDebug(_T("object found ->") + pElement->ToString());
                if (IsSelected(pElement) == false)
                {
                    if (nFlags & MK_SHIFT)
                    {
                    }
                    else
                        SelectNone();

                    pView->LogDebug(_T("object selected ->") + pElement->ToString());
                    m_objectId = pElement->m_objectId;
                    Select(pElement);
                    pElement->m_bMoving = true;
                }

                m_selectMode = SelectMode::move;
                pView->LogDebug(_T("selectMode == move"));

                // Update UI
                UpdateUI(pView, pElement);
                // Redraw
                Invalidate(pView, pElement);
            }
            else
            {
                // See if the click was on an object
                // TRUE -> select and start move if so
                // FALSE -> Click on background, start a net-selection
                // m_selectMode = netSelect;

                if (HasSelection())
                {
                    pView->LogDebug(_T("selection cleared"));
                    SelectNone();
                    Invalidate(pView, pElement);
                }
                m_selectPoint = point;
                m_selectMode = SelectMode::netselect;
                pView->LogDebug(_T("selectMode == netselect"));
            }
        }
    }
    // We are not in a select operation
    // -> this is a drawing operation
    // We have to create...
    // Create a Drawable Object...
    else
    {
        pView->LogDebug(_T("selection cleared"));
        SelectNone();

        std::shared_ptr<CElement> pNewElement = CFactory::CreateElementOfType(m_type, m_shapeType);
        if (m_type == ElementType::type_unknown)
        {
            pView->LogDebug(_T("object not implemented yet ! ->") + pNewElement->ToString());
            return;
        }

        pNewElement->m_point = point;
        // For plumbing purpose...
        pNewElement->m_pManager = this;
        pNewElement->m_pView = pView;

        // Add an object
        m_objects.AddTail(pNewElement);
        pView->LogDebug(_T("object created ->") + pNewElement->ToString());

        // Store last created object
        m_objectId = pNewElement->m_objectId;

        // Select the new element
        Select(pNewElement);
        pView->LogDebug(_T("object selected ->") + pNewElement->ToString());

        m_selectMode = SelectMode::size;
        pView->LogDebug(_T("selectMode == size"));

        pView->GetDocument()->SetModifiedFlag();

        // Update ClassView & FileView
        UpdateClassView();//pNewElement);
        UpdateFileView();//pNewElement);

        // Update UI
        UpdateUI(pView, pNewElement);
    }

}

void CElementManager::OnLButtonDblClk(CStartMenuViewEx* pView, UINT nFlags, const CPoint& cpoint)
{
    // Caution, it flicks !
    //pView->LogDebug(_T("CElementManager::OnLButtonDblClk"));

}

void CElementManager::DrawSelectionRect(CStartMenuViewEx* pView)
{
    /*
    CClientDC dc(pView);
    Graphics graphics(dc);
    //graphics.ScaleTransform(m_fZoomFactor, m_fZoomFactor);

    Color colorBlack(255, 0, 0, 0);
    Pen penBlack(colorBlack);
    CRect rect = m_selectionRect;

    graphics.DrawRectangle(&penBlack, rect.left, rect.top, rect.Width(), rect.Height());
    */
}

void CElementManager::OnMouseMove(CStartMenuViewEx* pView, UINT nFlags, const CPoint& cpoint)
{
    // Caution, it flicks !
    //pView->LogDebug(_T("CElementManager::OnMouseMove"));

    // a SELECT operation is started
    if (m_selectMode == SelectMode::none)
    {
    }

    //if( m_bDrawing == FALSE )
    //	return;

    CPoint point = cpoint;
    ViewToManager(pView, point);

    // Debugging
    CString str;
    str.Format(_T("point {%d,%d} / {%d,%d}"), cpoint.x, cpoint.y, point.x, point.y);
    //pView->LogDebug(str);

    if (m_selectMode == SelectMode::netselect)
    {
        //pView->LogDebug("selection is under drawing");

        CRect selectionRect(m_selectPoint.x, m_selectPoint.y, point.x, point.y);
        m_selectionRect = selectionRect;

        DrawSelectionRect(pView);
        return;
    }

    std::shared_ptr<CElement> pElement = m_selection.GetHead(); //m_objects.FindElement(m_objectId);
    if (pElement == NULL)
    {
        pView->LogDebug(_T("FindElement return NULL; return;"));
        return;
    }

    if (m_type == ElementType::type_select)
    {
        if (HasSelection())
        {
            // Change cursor look temporary just because mouse could be over a shape
            int nHandle = pElement->HitTest(point, pView, true);
            if (nHandle != 0)
            {
                SetCursor(pElement->GetHandleCursor(nHandle));
            }


            if (m_selectMode == SelectMode::move)
            {
                //pView->LogDebug("object selection moved ->" + pElement->ToString());

                for (vector<std::shared_ptr<CElement>>::const_iterator itSel = m_selection.m_objects.begin(); itSel != m_selection.m_objects.end(); itSel++)
                {
                    std::shared_ptr<CElement> pObj = *itSel;

                    CPoint delta = (CPoint)(point - m_lastPoint);
                    //std::shared_ptr<CElement> pObj = m_selection.GetHead();
                    InvalObj(pView, pObj);
                    pObj->m_rect += delta;
                    pObj->m_point = pObj->m_rect.TopLeft();
                    InvalObj(pView, pObj);
                }

                pView->GetDocument()->SetModifiedFlag();
            }
            if (m_selectMode == SelectMode::size)
            {
                if (m_nDragHandle != 0)
                {
                    //pView->LogDebug("object selection sized ->" + pElement->ToString());

                    std::shared_ptr<CElement> pObj = m_selection.GetHead();
                    pObj->MoveHandleTo(m_nDragHandle, point, pView);
                    // Find a connection ?
                    FindAConnectionFor(pObj, point, pView);
                    InvalObj(pView, pObj);

                    pView->GetDocument()->SetModifiedFlag();
                }
            }
        }
    }
    else
    {
        if (m_selectMode == SelectMode::size)
        {
            //pView->LogDebug("obect is under drawing ->" + pElement->ToString());

            pElement->m_last = point;
            pElement->InvalidateObj();
            // Find a connection ?
            FindAConnectionFor(pElement, point, pView);
            InvalObj(pView, pElement);

            pView->GetDocument()->SetModifiedFlag();
        }
    }

    m_lastPoint = point;

    // Check for mouse cursor -> sizing/moving
    if (m_selectMode == SelectMode::size)
    {
        //if (m_nDragHandle != 0)
        {
            SetCursor(m_selection.GetHead()->GetHandleCursor(m_nDragHandle));
        }
    }

    if (m_type == ElementType::type_select && m_selection.GetCount() == 0)
    {
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
    }
}


void CElementManager::OnLButtonUp(CStartMenuViewEx* pView, UINT nFlags, const CPoint& cpoint)
{
    // Caution, it flicks !
    //pView->LogDebug(_T("CElementManager::OnLButtonUp"));

    //if( m_selectMode == SelectMode::move || m_selectMode == SelectMode::size )
    {
        // Selection Moving or Sizing is finished. 
        // Nothing to do.
        m_selectMode = SelectMode::none;
    }

    //m_bDrawing = FALSE;

    CPoint point = cpoint;
    ViewToManager(pView, point);

    std::shared_ptr<CElement> pElement = m_objects.FindElement(m_objectId);
    if (pElement == NULL)
        return;

    if (m_type == ElementType::type_select)
    {
        if (HasSelection() && m_selection.GetCount() == 1)
        {
            // Nothing to do...
            pView->LogDebug(_T("object selection finished ->") + pElement->ToString());
        }
    }
    else
    {
        // Finish a drawing operation
        pElement->m_last = point;
        pElement->InvalidateObj();
        pElement->CheckForKeepingAMinimumSize();
        // Switch the view in Select Mode
        m_type = ElementType::type_select;

        pView->LogDebug(_T("object drawing finished ->") + pElement->ToString());
    }

    pElement->m_bMoving = FALSE;
    // Update UI
    UpdateUI(pView, pElement);
    // Redraw
    InvalObj(pView, pElement);

    m_selectMode = SelectMode::none;
    pView->GetDocument()->SetModifiedFlag();
}

void CElementManager::InvalObj(CStartMenuViewEx* pView, std::shared_ptr<CElement> pElement)
{
    CRect rect = pElement->m_rect;
    ManagerToView(pView, rect);
    if (pView->m_bActive && IsSelected(pElement))
    {
        rect.left -= 4;
        rect.top -= 5;
        rect.right += 5;
        rect.bottom += 4;
    }
    rect.InflateRect(1, 1); // handles CDrawOleObj objects

    pView->InvalidateRect(rect, FALSE);
    //FIXME:
    Invalidate(pView, pElement);
}

void CElementManager::Invalidate(CStartMenuViewEx* pView)
{
    pView->Invalidate(FALSE);
}

void CElementManager::Invalidate(CStartMenuViewEx* pView, std::shared_ptr<CElement> pElement)
{
    pView->Invalidate(FALSE);
}

void CElementManager::Update(CStartMenuViewEx* pView, LPARAM lHint, CObject* pHint)
{
    switch (lHint)
    {
    case HINT_UPDATE_WINDOW:    // redraw entire window
        pView->LogDebug(_T("CElementManager::Update HINT_UPDATE_WINDOW"));
        pView->Invalidate(FALSE);
        break;

    case HINT_UPDATE_DRAWOBJ:   // a single object has changed
    {
        pView->LogDebug(_T("CElementManager::Update HINT_UPDATE_DRAWOBJ"));
        CElement* p = (CElement*)pHint;
        InvalObj(pView, std::shared_ptr<CElement>(p));
    }
    break;

    case HINT_UPDATE_SELECTION: // an entire selection has changed
    {
        pView->LogDebug(_T("CElementManager::Update HINT_UPDATE_SELECTION"));
        pView->Invalidate(FALSE);
        //CElementContainer * pList = pHint != NULL ? (CElementContainer*)pHint : &m_selection;
        //POSITION pos = pList->m_objects.GetHeadPosition();
        //while (pos != NULL)
        //{
        //	CElement * pElement = pList->m_objects.GetNext(pos);
        //	InvalObj(pView, pElement);

        //	// Update UI
        //	UpdateUI(pView, pElement);
        //}			
    }
    break;

    case HINT_DELETE_SELECTION: // an entire selection has been removed
        /*
        if (pHint != &m_selection)
        {
            CDrawObjList* pList = (CDrawObjList*)pHint;
            POSITION pos = pList->GetHeadPosition();
            while (pos != NULL)
            {
                CDrawObj* pObj = pList->GetNext(pos);
                InvalObj(pObj);
                Remove(pObj);   // remove it from this view's selection
            }
        }
        */
        break;

    case HINT_UPDATE_OLE_ITEMS:
        /*
        {
            CDrawDoc* pDoc = GetDocument();
            POSITION pos = pDoc->GetObjects()->GetHeadPosition();
            while (pos != NULL)
            {
                CDrawObj* pObj = pDoc->GetObjects()->GetNext(pos);
                if (pObj->IsKindOf(RUNTIME_CLASS(CDrawOleObj)))
                    InvalObj(pObj);
            }
        }
        */
        break;

    default:
        ASSERT(FALSE);
        break;
    }
}

void CElementManager::UpdateClassView()
{
    std::shared_ptr<CElement> pNullElement;
    UpdateClassView(pNullElement);
    for (vector<std::shared_ptr<CElement>>::const_iterator i = GetObjects().begin(); i != GetObjects().end(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        UpdateClassView(pElement);
    }
}

void CElementManager::UpdateClassView(std::shared_ptr<CElement> pElement)
{
    CWnd* p = AfxGetMainWnd();
    CMainFrame* pmf = (CMainFrame*)p;
    if (pElement == NULL)
        pmf->InitClassView();
    else
        pmf->UpdateClassViewFromObject(pElement);
}

void CElementManager::UpdateFileView()
{
    std::shared_ptr<CElement> pNullElement;
    UpdateFileView(pNullElement);
    for (vector<std::shared_ptr<CElement>>::const_iterator i = GetObjects().begin(); i != GetObjects().end(); i++)
    {
        std::shared_ptr<CElement> pElement = *i;
        UpdateFileView(pElement);
    }
}

void CElementManager::UpdateFileView(std::shared_ptr<CElement> pElement)
{
    CWnd* p = AfxGetMainWnd();
    CMainFrame* pmf = (CMainFrame*)p;
    if (pElement == NULL)
        pmf->InitFileView();
    else
        pmf->UpdateFileViewFromObject(pElement);
}

void CElementManager::UpdateUI(CStartMenuViewEx* pView, std::shared_ptr<CElement> pElement)
{
    // Update Property Grid
    UpdatePropertyGrid(pView, pElement);
    // Update Ribbon UI
    UpdateRibbonUI(pView, pElement);
}

void CElementManager::UpdatePropertyGrid(CStartMenuViewEx* pView, std::shared_ptr<CElement> pElement)
{
    CWnd* p = AfxGetMainWnd();
    CMainFrame* pmf = (CMainFrame*)p;
    //pmf->UpdatePropertiesFromObject(pElement);
}

void CElementManager::UpdateRibbonUI(CStartMenuViewEx* pView, std::shared_ptr<CElement> pElement)
{
    CWnd* p = AfxGetMainWnd();
    CMainFrame* pmf = (CMainFrame*)p;
    //pmf->UpdateRibbonUI(pView);
}

void CElementManager::UpdateFromPropertyGrid(std::wstring objectId, std::wstring name, std::wstring value)
{
    bool bUpdateUI = false;
    std::shared_ptr<CElement> pElement = m_objects.FindElement(objectId);
    if (pElement == NULL)
    {
        return;
    }

    if (name == prop_Name)
    {
        pElement->m_name = value;
        bUpdateUI = true;
    }

    if (name == prop_Caption)
    {
        pElement->m_caption = value;
    }

    if (name == prop_Text)
    {
        pElement->m_text = value;
    }

    if (name == prop_Image)
    {
        pElement->m_image = value;
    }

    if (name == prop_Font_Name)
    {
        pElement->m_fontName = value;
    }

    // Some properties could change the UI in class view or file view
    if (bUpdateUI == true)
    {
        this->UpdateClassView();
        this->UpdateFileView();
    }
    InvalObj(pElement->GetView(), pElement);
}

void CElementManager::UpdateFromPropertyGrid(std::wstring objectId, std::wstring name, COLORREF color)
{
    std::shared_ptr<CElement> pElement = m_objects.FindElement(objectId);
    if (pElement == NULL)
    {
        return;
    }

    if (name == prop_Fill_Color)
    {
        pElement->m_colorFill = color;
    }

    if (name == prop_Line_Color)
    {
        pElement->m_colorLine = color;
    }

    UpdateRibbonUI(pElement->GetView(), pElement);
    InvalObj(pElement->GetView(), pElement);
}

void CElementManager::UpdateFromPropertyGrid(std::wstring objectId, std::wstring name, long value)
{
    std::shared_ptr<CElement> pElement = m_objects.FindElement(objectId);
    if (pElement == NULL)
    {
        return;
    }

    if (name == prop_Left)
    {
        pElement->m_rect.left = value;
    }

    if (name == prop_Right)
    {
        pElement->m_rect.right = value;
    }

    if (name == prop_Top)
    {
        pElement->m_rect.top = value;
    }

    if (name == prop_Bottom)
    {
        pElement->m_rect.bottom = value;
    }

    if (name == prop_Has_Fill_Color)
    {
        pElement->m_bColorFill = value == 0 ? false : true;
    }

    if (name == prop_Is_Fill_Solid_Color)
    {
        pElement->m_bSolidColorFill = value == 0 ? false : true;
    }

    if (name == prop_Has_Line_Color)
    {
        pElement->m_bColorLine = value == 0 ? false : true;
    }

    if (name == prop_Font_Size)
    {
        pElement->m_fontSize = value;
    }

    InvalObj(pElement->GetView(), pElement);
}

void CElementManager::ActivateView(CStartMenuViewEx* pView, bool bActivate, CView* pActiveView, CView* pDeactiveView)
{
    // invalidate selections when active status changes
    if (pView->m_bActive != bActivate)
    {
        if (bActivate)  // if becoming active update as if active
            pView->m_bActive = bActivate;
        if (HasSelection())
            Update(pView, HINT_UPDATE_SELECTION, NULL);
        pView->m_bActive = bActivate;

        // Initiate the connection with the Property Window
        ConnectToPropertyGrid();
        ConnectToMainFrame(pView);
        // Update ClassView & FileView
        UpdateClassView();
        UpdateFileView();
    }

    //((CMainFrame*)AfxGetMainWnd())->UpdateUI(this);
    //((CMainFrame*)AfxGetMainWnd())->UpdateContextTab(this);
}

void CElementManager::ConnectToMainFrame(CStartMenuViewEx* pView)
{
    CWnd* p = AfxGetMainWnd();
    CMainFrame* pmf = (CMainFrame*)p;
    pmf->SetView(pView);
}

void CElementManager::DebugDumpObjects(CStartMenuViewEx* pView)
{
    pView->LogDebug(_T("Dumping m_objects..."));
    m_objects.DebugDumpObjects(pView);
    pView->LogDebug(_T("Dumping m_selection..."));
    m_selection.DebugDumpObjects(pView);
}

void CElementManager::NoFillColor(CStartMenuViewEx* pView)
{
    //POSITION pos = m_selection.m_objects.GetHeadPosition();
    //while (pos != NULL)
    //{
    //	CElement * pElement = m_selection.m_objects.GetNext(pos);
    //	if (pElement->CanChangeFillColor())
    //	{
    //		pElement->m_bColorFill = FALSE;
    //	}
    //}

    std::shared_ptr<CElement> pElement = m_selection.GetHead();
    if (pElement->CanChangeFillColor())
    {
        pElement->m_bColorFill = FALSE;
    }

    Invalidate(pView);
}

void CElementManager::FillColor(CStartMenuViewEx* pView)
{
    COLORREF color = ((CMainFrame*)AfxGetMainWnd())->GetColorFromColorButton(ID_FORMAT_FILLCOLOR);

    if (color == (COLORREF)-1)
    {
        return;
    }

    //POSITION pos = m_selection.m_objects.GetHeadPosition();
    //while (pos != NULL)
    //{
    //	CElement * pElement = m_selection.m_objects.GetNext(pos);
    //	if (pElement->CanChangeFillColor())
    //	{
    //		pElement->m_colorFill = color;
    //		pElement->m_bColorFill = true;
    //	}
    //}

    std::shared_ptr<CElement> pElement = m_selection.GetHead();
    if (pElement->CanChangeFillColor())
    {
        pElement->m_colorFill = color;
        pElement->m_bColorFill = true;
    }

    Invalidate(pView);
}

void CElementManager::LineColor(CStartMenuViewEx* pView)
{
    COLORREF color = ((CMainFrame*)AfxGetMainWnd())->GetColorFromColorButton(ID_FORMAT_LINECOLOR);

    if (color == (COLORREF)-1)
    {
        return;
    }

    //POSITION pos = m_selection.m_objects.GetHeadPosition();
    //while (pos != NULL)
    //{
    //	CElement * pElement = m_selection.m_objects.GetNext(pos);
    //	if (pElement->CanChangeLineColor())
    //	{
    //		pElement->m_colorLine = color;
    //		pElement->m_bColorLine = true;
    //	}
    //}

    std::shared_ptr<CElement> pElement = m_selection.GetHead();
    if (pElement->CanChangeLineColor())
    {
        pElement->m_colorLine = color;
        pElement->m_bColorLine = true;
    }

    Invalidate(pView);
}

void CElementManager::LineWidth(CStartMenuViewEx* pView, UINT nID)
{
    int weight = -1;
    if (nID == ID_FORMAT_LINEWIDTH)
    {
        weight = ((CMainFrame*)AfxGetMainWnd())->GetWidthFromLineWidth(ID_FORMAT_LINEWIDTH);
    }
    else if (nID == ID_FORMAT_LINEWIDTH_MORE)
    {
        /*
        CLineWeightDlg dlg(AfxGetMainWnd());

        if (m_selection.GetCount() == 1)
        {
            dlg.m_penSize = m_selection.GetHead()->IsEnableLine() ? m_selection.GetHead()->GetLineWeight() : 0;
        }

        if (dlg.DoModal() == IDOK)
        {
            weight = dlg.m_penSize;
        }
        */
    }

    if (weight == -1)
    {
        return;
    }

    //POSITION pos = m_selection.m_objects.GetHeadPosition();
    //while (pos != NULL)
    //{
    //	CElement * pElement = m_selection.m_objects.GetNext(pos);
    //	if (pElement->CanChangeLineWidth())
    //	{
    //		pElement->m_bLineWidth = weight > 0;
    //		pElement->m_lineWidth = weight;
    //	}
    //}

    std::shared_ptr<CElement> pElement = m_selection.GetHead();
    if (pElement->CanChangeLineWidth())
    {
        pElement->m_bLineWidth = weight > 0;
        pElement->m_lineWidth = weight;
    }

    Invalidate(pView);
}

void CElementManager::PageColor(CStartMenuViewEx* pView)
{
}

void CElementManager::Zoom(CStartMenuViewEx* pView)
{
    //m_fZoomFactor += 0.10f;
    //Invalidate(pView);
}

void CElementManager::ZoomIn(CStartMenuViewEx* pView)
{
    m_fZoomFactor += 0.10f;
    Invalidate(pView);
}

void CElementManager::ZoomOut(CStartMenuViewEx* pView)
{
    m_fZoomFactor -= 0.10f;
    Invalidate(pView);
}

void CalcAutoPointRect2(int count, std::shared_ptr<CElement> pNewElement)
{
    int x = count % 20;
    int y = count % 20;

    pNewElement->m_point.x = 50 * x;
    pNewElement->m_point.y = 50 * y;

    pNewElement->m_rect.top = pNewElement->m_point.y;
    pNewElement->m_rect.left = pNewElement->m_point.x;
    pNewElement->m_rect.bottom = pNewElement->m_point.y + 100;
    pNewElement->m_rect.right = pNewElement->m_point.x + 100;
}

void CalcAutoPointRect(int count, std::shared_ptr<CElement> pNewElement)
{
    static bool flag = true;
    int c = 0;
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            if (count % 400 == c)
            {
                pNewElement->m_point.x = 75 * x;
                pNewElement->m_point.y = 75 * y;

                flag = (flag == true ? false : true);
                if (flag == true)
                {
                    pNewElement->m_point.y += 20;
                }
                else
                {
                    pNewElement->m_point.y += 10;
                }

                pNewElement->m_rect.left = pNewElement->m_point.x;
                pNewElement->m_rect.top = pNewElement->m_point.y;
                pNewElement->m_rect.right = pNewElement->m_point.x + 80 + 10;
                pNewElement->m_rect.bottom = pNewElement->m_point.y + 80 + 10;
                return;
            }

            c++;
        }
    }
}

void CElementManager::FindAConnectionFor(std::shared_ptr<CElement> pElement, CPoint point, CStartMenuViewEx* pView)
{
}

void CElementManager::LoadStartMenu(CStartMenuViewEx* pView)
{
    // Rmove all graphic objects
    m_objects.RemoveAll();

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;

    int count = 1;
    map<wstring, int> mapAppz;
    for (shared_ptr<ApplicationLink> link : pMainFrame->GetManager()->m_Links)
    {
        if (link->_hIcon == 0)
            continue;

        //HICON hIcon = link->_hIcon;
        mapAppz[link->_name] = count;
        ++count;
    }

    count = 0;
    for (shared_ptr<ApplicationLink> link : pMainFrame->GetManager()->m_Links)
    {
        //lvItem.pszText = (LPTSTR)link->_name.c_str();

        std::wstring slink = link->_name;
        if (slink.find(_T(".lnk")) == wstring::npos)
        {
            continue;
        }

        std::shared_ptr<CElement> pNewElement = CFactory::CreateElementOfType(ElementType::type_start_menu,
            ShapeType::start_menu_element);
        CElement* pElement = pNewElement.get();
        CStartMenuElement* pSMElement = (CStartMenuElement*)pElement;

        pSMElement->m_attr.m_Name = link->_name;
        pNewElement->m_text = (CStringW)pSMElement->m_attr.m_Name.c_str();

        CalcAutoPointRect(count, pNewElement);
        pNewElement->m_pManager = this;
        pNewElement->m_pView = pView;

        // Add a graphic object
        m_objects.AddTail(pNewElement);
        pView->LogDebug(_T("object created ->") + pNewElement->ToString());

        ++count;
    }

    pView->Invalidate();
}

void CElementManager::OnSearchGo(CStartMenuViewEx* pView)
{
    USES_CONVERSION;

    // Rmove all graphic objects
    m_objects.RemoveAll();

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;

    CMFCRibbonBar* pRibbon = pMainFrame->GetRibbonBar();
    CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_EDIT_NAME));
    if (pEdit == NULL)
    {
        return;
    }

    CString strSearch = pEdit->GetEditText().MakeUpper();

    // TODO: Add your command handler code here
    if (strSearch.IsEmpty())
    {
        LoadStartMenu(pView);
        return;
    }

    int count = 1;
    map<wstring, int> mapAppz;
    for (shared_ptr<ApplicationLink> link : pMainFrame->GetManager()->m_Links)
    {
        if (link->_hIcon == 0)
            continue;

        //HICON hIcon = link->_hIcon;
        mapAppz[link->_name] = count;
        ++count;
    }

    count = 0;
    for (shared_ptr<ApplicationLink> link : pMainFrame->GetManager()->m_Links)
    {
        //lvItem.pszText = (LPTSTR)link->_name.c_str();

        std::wstring slink = ToUpper(link->_name);
        if (slink.find(_T(".LNK")) == wstring::npos)
        {
            continue;
        }

        if (slink.find(strSearch) == wstring::npos)
        {
            continue;
        }

        std::shared_ptr<CElement> pNewElement = CFactory::CreateElementOfType(ElementType::type_start_menu,
            ShapeType::start_menu_element);
        CElement* pElement = pNewElement.get();
        CStartMenuElement* pSMElement = (CStartMenuElement*)pElement;

        pSMElement->m_attr.m_Name = link->_name;
        pNewElement->m_text = (CStringW)pSMElement->m_attr.m_Name.c_str();

        CalcAutoPointRect(count, pNewElement);
        pNewElement->m_pManager = this;
        pNewElement->m_pView = pView;

        // Add a graphic object
        m_objects.AddTail(pNewElement);
        pView->LogDebug(_T("object created ->") + pNewElement->ToString());

        ++count;
    }

    pView->Invalidate();
}

void CElementManager::OnSearchReset(CStartMenuViewEx* pView)
{
    USES_CONVERSION;

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;

    CMFCRibbonBar* pRibbon = pMainFrame->GetRibbonBar();
    CMFCRibbonEdit* pEdit = DYNAMIC_DOWNCAST(CMFCRibbonEdit, pRibbon->FindByID(ID_EDIT_NAME));
    if (pEdit == NULL)
    {
        return;
    }

    pEdit->SetEditText(_T(""));
    LoadStartMenu(pView);
}

