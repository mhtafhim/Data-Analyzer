# Data Analyzer

A comprehensive MFC (Microsoft Foundation Classes) desktop application for visualizing and analyzing data from text files. This application provides an intuitive interface for loading tabular data, viewing it in multiple formats, and generating interactive charts.

## Features

### Core Functionality
- **Load Data**: Import data from text files with automatic header detection and parsing
- **Data Viewing**: Display loaded data in a structured list/table format
- **Data Hierarchy**: Browse data structure through a tree view control
- **Interactive Charts**: Visualize data using various chart types with the integrated ChartCtrl library

### Tab-Based Interface

#### Tab One - Chart Analysis
- **Chart Generation**: Create line charts from your data
- **Dual-Axis Selection**: Choose two different data columns to visualize
- **Dynamic Combo Boxes**: Select data columns for X and Y axes
- **Chart Customization**: Includes grid lines, axis labels, and cross-hair cursors
- **Export Options**: 
  - Export graphs as images
  - Export data from charts

#### Tab Two - Analysis Tools
- Additional analysis features (extensible framework for future enhancements)

## Project Structure

```
Data-Analyzer/
├── Data Analyzer.h               # Main application header
├── Data Analyzer.cpp             # Main application implementation
├── Data AnalyzerDlg.h            # Main dialog header
├── Data AnalyzerDlg.cpp          # Main dialog implementation
├── Tab_One.h / Tab_One.cpp       # First tab (charting)
├── Tab_Two.h / Tab_Two.cpp       # Second tab (analysis)
├── ChartCtrl/                    # Chart control library
│   ├── ChartCtrl.h/cpp           # Main chart control
│   ├── ChartAxis*.h/cpp          # Axis implementations
│   ├── ChartSerie*.h/cpp         # Chart series types (Line, Bar, Points, etc.)
│   ├── ChartCursor*.h/cpp        # Cursor implementations
│   └── ...                       # Additional chart utilities
├── Data Analyzer.sln             # Visual Studio solution
├── Data Analyzer.vcxproj         # Visual Studio project
└── resource.h / .rc              # Resource definitions
```

## Requirements

- **Operating System**: Windows
- **Development Environment**: Visual Studio (with MFC support)
- **Framework**: MFC (Microsoft Foundation Classes)
- **C++ Standard**: C++11 or later
- **Additional Libraries**: ChartCtrl (included in project)

## Building

1. Open `Data Analyzer.sln` in Visual Studio
2. Ensure the MFC development tools are installed
3. Build the solution (Build → Build Solution or Ctrl+Shift+B)
4. The executable will be generated in the output directory

## Usage

### Loading Data
1. Click the **Load** button on the main dialog
2. Select a text file containing your data
3. The data will be parsed and displayed in the table view
4. Column headers will be automatically detected from the first row

### Creating Charts
1. Navigate to the **Chart Analysis** tab
2. Select data columns from the dropdown menus
3. Click the **Plot** button to generate the chart
4. The chart will display with interactive features

### Exporting Data
1. Right-click on a generated chart
2. Choose **Export Graph** to save the chart as an image
3. Choose **Export Data** to export the underlying data

## Data Format

The application expects data files in the following format:
- **Delimiters**: Whitespace or comma-separated values
- **Headers**: First row should contain column names
- **Data**: Numerical values in subsequent rows
- **Example**:
  ```
  Date     Temperature   Humidity   Pressure
  2024-01-01  20.5       65.2      1013.25
  2024-01-02  21.3       63.8      1012.90
  ```

## Architecture

### Key Classes

- **CDataAnalyzerApp**: Main application class inheriting from `CWinApp`
- **CDataAnalyzerDlg**: Main dialog window managing UI layout and file I/O
- **Tab_One**: Chart visualization interface with combo box selection
- **Tab_Two**: Extensible analysis framework
- **CChartCtrl**: Professional charting control from the included library

### Data Flow

1. User loads file via dialog
2. `LoadTextFile()` parses the file into headers and data vectors
3. `InitTable()` populates the list control with parsed data
4. User selects columns and generates charts
5. Chart displays with interactive features (zoom, pan, export)

## Extending the Application

### Adding New Chart Types
1. Include the appropriate chart series header in `Tab_One.cpp`
2. Modify the chart generation logic in `Tab_One::OnBnClickedButton1()`
3. Add UI controls for chart type selection

### Adding New Data Processing Features
1. Extend `Tab_Two` dialog implementation
2. Add data processing algorithms
3. Link to main dialog data members

## Known Features

- File loading and parsing
- Multi-column data visualization
- Interactive chart controls with zoom and pan
- Right-click context menu for export options
- Tree view for data structure representation
- Dynamic UI updates based on loaded data

## Future Enhancements

- Support for CSV and Excel file formats
- Statistical analysis tools
- Data filtering and sorting
- Additional chart types (bar, pie, scatter)
- Real-time data updates
- Data export to multiple formats

## License

This project is part of the Frontier Data Analysis suite.

## Support

For issues or questions regarding this application, please refer to the project documentation or contact the development team.

---

**Version**: 1.0  
**Last Updated**: 2024  
**Platform**: Windows (MFC)
