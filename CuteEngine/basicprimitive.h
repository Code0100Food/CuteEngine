#ifndef BASICPRIMITIVE_H
#define BASICPRIMITIVE_H

#include "component.h"
#include <QColor>
#include <QColorDialog>

class QPaintEvent;
class QComboBox;
class QLabel;
class Transform;
class QVBoxLayout;
class QPushButton;
class QSpinBox;

enum E_PRIMITIVE_TYPE
{
    PT_CIRCLE = 0,
    PT_RECTANGLE,
    PT_MAX_PRIMITIVE
};

enum E_LINE_TYPE
{
    LT_SOLID = 0,
    LT_DASH,
    LT_DOT,
    LT_MAX
};

class ColorDialog : public QWidget
{
public:
    QColor PickColor()
    {
        QColor color = QColorDialog::getColor(Qt::yellow, this );
        if(color.isValid())
        {
            return color;
        }
    }
};

class BasicPrimitive : public Component
{
    Q_OBJECT

public:

    BasicPrimitive(E_PRIMITIVE_TYPE _type = PT_CIRCLE);
    ~BasicPrimitive() override;

    void Update() override;

public:

    void SetX(int _x);
    void SetY(int _y);
    void SetWidth(int _width);
    void SetHeight(int _height);

    int GetX()const;
    int GetY()const;
    int GetWidth()const;
    int GetHeight()const;

    void SetColor(QColor _color);
    void SetEdgeColor(QColor _edge_color);
    const QColor GetColor() const;
    const QColor GetEdgeColor() const;

    void SetLineType(E_LINE_TYPE _type);
    E_LINE_TYPE GetLineType() const;
    Qt::PenStyle QtGetLineType() const;
    int GetEdgeWidth()const;

    E_PRIMITIVE_TYPE GetPrimitiveType() const;

    void Connect(Transform* target_trans);
    void SetTransformValues(Transform* target_trans);

    void GoToInspector(QVBoxLayout* inspector_layout) override;
    void ShowUI() override;
    void HideUI() override;

private:

    float x = 0.0f;
    float y = 0.0f;
    float width = 1.0f;
    float height = 1.0f;

    QColor color;
    QColor edge_color;
    E_PRIMITIVE_TYPE primitive_type;
    E_LINE_TYPE line_type;
    int edge_width;

    QLabel* title = nullptr;
    QVBoxLayout* layout = nullptr;
    QComboBox* select_primitive_box = nullptr;
    QComboBox* select_line_type_box = nullptr;
    QLabel* edge_width_label = nullptr;
    QSpinBox* edge_width_spin_box = nullptr;
    QPushButton* pick_edge_color_btn = nullptr;
    QPushButton* pick_color_btn = nullptr;

public slots:

    void SetXPosition(double x_pos);
    void SetYPosition(double y_pos);

    void SetXScale(double x_pos);
    void SetYScale(double y_pos);

    void ChangePrimitive();
    void SetLineTypeComboBox();
    void SetEdgeWidth(int value);
    void SetColorFromColorPicker();
    void SetEdgeColorFromColorPicker();

};

#endif // BASICPRIMITIVE_H
