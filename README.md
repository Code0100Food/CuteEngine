# CuteEngine
A simple editor of scenes made of vector shapes.

## Created by:
- [Marc Latorre](https://github.com/marclafr)
- [Ferran Martin](https://github.com/ferranmartinvila)
- [Eric Solà](https://github.com/HeladodePistacho)

## User guide

### Hierarchy
- Add Entity: With the button "Add Entity" you can add a new entity to the scene, that will appear in the hierarchy just as it is created.
- Remove Entity: You can remove those entities with the "Remove Entity" button if the entity you want to remove is selected.

FOTO Hierarchy

### Inspector
FOTO INSPECTOR

#### Name
You can change the name of the entity in the inpector and it is updated in the hierarchhy as well.

#### Transformation
Controls the position, rotation and scale of the entity. You can see the changes in the scene if you have something to render.

#### Mesh
Selected mesh that is rendered on the scene from the loaded meshes on the resources.
In order to change the mesh selected there is a droplist to choose from.

#### Light
Adds a directional light into the scene.
You can change the light color and intensity.

#### Toggle grid
A toggle to decide if the grid should be rendered or not in the scene.

### Resources
List of the loaded resources. Includes meshes and textures.

#### Load resources
In order to load a resource simply drag and drop them on the engine.

FOTO RESOURCES

### Menu Bar

- Open project: Open the project selected in the dialog window and close the current one.
- Close project: Closes the actual project.

![](FOTO MENU BAR)

#### Render mode
From the menu bar you can chose a render mode in order to show the resultant texture of a concrete render process. You can choose from the following:
- Shaded color: All the textures mode combined, in other words the final result.
- Normals: Shows the normals of the current rendered meshes.
- Depth: Shows the depth buffer (Z buffer).
- Albedo: Shows the color of the scene.
- Selection: The texture used to generate the selected effect. In this mode we can see the selected object drawn in white.

### Camera controls

### Grid

### Bloom

### Selection
