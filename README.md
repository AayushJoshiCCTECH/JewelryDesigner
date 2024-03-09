# JewelryDesigner

## Description
This app allows users to customize jewelry shapes (pendants) using Bezier curves. Users can interact with the shapes in real-time, selecting different curves and points to customize, adding new control points and the modifying existing ones.

## Core Components

### Geometry
- `Point3D`: Represents 3D points, used as control points for the Bezier curves.
- `Shapes3D`: Abstract base class for 3D shapes. Provides a common interface for all shapes.
- `Droplet3D`: Represents a 3D droplet shape. Inherits from `Shapes3D`.
- `Heart3D`: Represents a 3D heart shape. Inherits from `Shapes3D`.

### Bezier Curve Calculation
- `Bezier`: Handles the calculation of Bezier curves, used to generate the shapes.

### Visualization and Interaction
- `OpenGLWindow`: Manages the OpenGL rendering of the shapes.
- `Visualizer`: Main window class that handles user interactions and updates the visualization based on user inputs.

## Features
- **Shape Selection**: Users can select between different shapes (e.g., heart, droplet) to customize.
- **Curve Selection**: Users can select specific curves within a shape to customize.
- **Add Control Points**: Users can add new control points to customize the shape of the jewelry.
- **Modify Control Points**: Existing control points can be modified to adjust the shape.
- **Real-Time Updates**: The shape updates in real-time as users make modifications.

## Usage
The app provides a graphical interface where users can interact with the jewelry shapes. Users can select a shape, add or modify control points, and see the changes reflected in the rendered shape.

## Output

https://github.com/AayushJoshiCCTECH/JewelryDesigner/assets/158051740/f4a07d86-241d-49e9-ae26-b0f81f4b900d


