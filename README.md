# CuteEngine
A simple editor of scenes made of vector shapes.

## Created by:
- [Marc Latorre](https://github.com/marclafr)
- [Ferran Martin](https://github.com/ferranmartinvila)
- [Eric Solà](https://github.com/HeladodePistacho)

## Features

### Menu Bar


### Hierarchy
- Add Entity: With the button "Add Entity" you can add a new entity to the scene, that will appear in the hierarchy just as it is created.
- Remove Entity: You can remove those entities with the "Remove Entity" button if the entity you want to remove is selected.

### Inspector
- Name: You can change the name of the entity in the inpector and it is updated in the hierarchhy as well.
- Add Component: A button that allows to add a new component to the entity.
- List of Components: All the components that the entity has appear in the inspector
  - Transform: Controls the position, rotation and scale of the entity. You can see the changes in the scene if you have something to render.
  - Basic Primitive: Creates a basic primitve that renders in the scene. There are several options to change the primitive:
    - Type of primitive
      - Circle
      - Rectangle
    - Type of edge line
      - Solid Line
      - Dash Line
      - Dot Line
    - Edge Width: Controls the width of the edge. If 0, there is no edge in the primitive
    - Pick Color: Opens a window to select a color. Can change the color of the primitive
    - Pick Edge Color: Opens a window to select a color. Can change the color of the edge of the primitive.

### Scene
- Renders all the primitives that are in the hierarchy with the options selected in the inspector of each entity.

## Qt Features used in the application

### Slots
- Basic Primitive
  - void SetXPosition(double x_pos);
  - void SetYPosition(double y_pos)
  - void SetXScale(double x_pos);
  - void SetYScale(double y_pos)
  - void ChangePrimitive();
  - void SetLineTypeComboBox();
  - void SetEdgeWidth(int value);
  - void SetColorFromColorPicker();
  - void SetEdgeColorFromColorPicker();

- Hierarchy
  - void AddEntity();
  - void RemoveEntity();
  - void SelectedEntity();
  
- Inspector
  - void AddComponent();
  - void CreateTransformation();
  - void CreateBasicPrimitive();
  - void Rename();

- Main Window
  - void Update();
  - void openProject();
  - void saveProject();
  - void customExit();
  
- Transform
  - void SetXPosition(double value);
  - void SetYPosition(double value);
  - void SetZPosition(double value);
  - void SetXRotation(double value);
  - void SetYRotation(double value);
  - void SetZRotation(double value);
  - void SetXScale(double value);
  - void SetYScale(double value);
  - void SetZScale(double value);
