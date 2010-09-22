/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2009 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#ifndef APPLICATION_LAYERIO_LAYEREXPORTER_H
#define APPLICATION_LAYERIO_LAYEREXPORTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif 

// STL includes
#include <vector>
#include <string>
#include <map>

// Boost includes
#include <boost/filesystem.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

// Core includes
#include <Core/DataBlock/DataType.h>
#include <Core/Utils/EnumClass.h>
#include <Core/Utils/Log.h>

// Application includes
#include <Application/Layer/Layer.h>

namespace Seg3D
{

// ------------------------------------------------------
// CLASS LayerImporterMode:
// The modes that define how data can be imported

// LayerImporterMode class definition
CORE_ENUM_CLASS
(
  LayerExporterMode,
  // -- UNKNOWN --
  // Invalid importer mode
  INVALID_E = 0x0000,

  // -- DATA --
  // Convert the data into a data volume
  DATA_E = 0x0001,

  // -- SINGLE_MASK --
  // Convert the data such that every value that is not zero is assumed to indicate the
  // mask.
  SINGLE_MASK_E = 0x0002,
  
  // -- BIT_MASKS --
  // Every bitplane that has a bit set will be assumed to be a separate mask
  BITPLANE_MASK_E   = 0x0004,

  // -- LABEL_MASKS --
  // Each separate number is interpreted as a separate mask
  LABEL_MASK_E = 0x0008 
)


std::string ExportToString( LayerExporterMode mode );
bool ImportFromString( const std::string& export_type_string, LayerExporterMode& mode );

// ------------------------------------------------------
// CLASS LayerExporter:
// The LayerExporter class abstracts the process of exporting a layer

// This is a base class from which exporters are sub classed
// The following functions need to be implemented:

// get_grid_transform: Get the transform of the dataset for the information display screen
// get_data_type: Get the data type for the information display screen

// forward declaration
class LayerExporter;
typedef boost::shared_ptr< LayerExporter >LayerExporterHandle;
typedef boost::weak_ptr< LayerExporter > LayerExporterWeakHandle;

// class definition
class LayerExporter : public boost::noncopyable
{
  // -- Constructor/Destructor --
public:
  // Construct a new layer file exporter for a specific file
  LayerExporter( std::vector< LayerHandle >& layers );

  // Virtual destructor for memory management of derived classes
  virtual ~LayerExporter();

  // These functions define the properties of the exporter and are implemented
  // by the SCI_EXPORTER_TYPE macro

  // -- Get the properties of this exporter --
  // These properties are generated by the SCI_EXPORTER_TYPE macro
public:
  // Name of the exporter (to be listed in the file filter dialog)
  virtual std::string name() const = 0;
  
  // The file types (extentions) that the exporter handles
  virtual std::string file_types() const = 0;

  // -- internals of the exporter -- 
protected:
  // LAYERS_:
  std::vector< LayerHandle > layers_;
  
  // -- Error handling --
public:
  // GET_ERROR:
  // Get the last error recorded in the exporter
  std::string get_error() const 
  { 
    return error_; 
  }

protected:
  // SET_ERROR:
  // Set the error message
  void set_error( const std::string& error )
  {
    error_ = error;
  }

private:
  std::string error_; 
  
  
public:
  // GET_GRID_TRANSFORM:
  // Get the grid transform of the grid that we are exporting
  virtual Core::GridTransform get_grid_transform() = 0;

  // GET_DATA_TYPE:
  // Get the type of data that is being exported
  virtual Core::DataType get_data_type() = 0;
  
  // GET_IMPORTER_MODES
  // Get then supported exporter modes
  virtual int get_exporter_modes() = 0;
  
  // SET_LABEL_LAYER_VALUES:
  // this is used to set the values for the layers when exporting a label and for nothing else
  virtual void set_label_layer_values( std::vector< double > values ){}

  // -- Export the layer as a specific type --  
public: 

  // EXPORT_LAYER
  // Export the layer to file
  virtual bool export_layer( LayerExporterMode mode, const std::string& file_path, 
    const std::string& name ) = 0;
};


// SCI_EXPORTER_TYPE:
// This macro should be defined at the top of each LayerExporter. It renders 
// code that allows both the class as well as the object to determine what its 
// properties are. By defining class specific static functions the class 
// properties can be queried without instantiating the object. On the other
// hand you want to query these properties from the object as well, even when
// we only have a pointer to the base object. Hence we need virtual functions
// as well. 

// Note: one would expect to use virtual static functions, but those are not
// allowed in C++, hence this macro ensures a consistent definition.

#define SCI_EXPORTER_TYPE(exporter_name,exporter_file_types) \
  public: \
    static std::string  Name()       { return exporter_name; }\
    static std::string  FileTypes()  { return exporter_file_types; }\
    \
    virtual std::string  name() const       { return Name(); } \
    virtual std::string  file_types() const { return FileTypes(); } \

} // end namespace seg3D

#endif
