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

#ifndef APPLICATION_INTERFACEMANAGER_INTERFACEMANAGER_H
#define APPLICATION_INTERFACEMANAGER_INTERFACEMANAGER_H

// STL includes
#include <string>
#include <map>
#include <set>

// Boost includes

#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

// Core includes
#include <Core/Utils/Log.h>
#include <Core/Utils/Exception.h>

// Application includes
#include <Core/State/StateHandler.h>

namespace Seg3D
{

// CLASS INTERFACEMANAGER
// This class manages the layout of the application

// Forward Declaration
class InterfaceManager;

// Class Definition
class InterfaceManager : public Core::StateHandler
{
	CORE_SINGLETON( InterfaceManager );

	// -- constructor/destructor --
private:
	InterfaceManager();
	virtual ~InterfaceManager();

	// -- state variables of interface --
public:
	// Whether the view is in full screen mode
	Core::StateBoolHandle full_screen_state_;
	
	// Dock widget visibility states
	Core::StateBoolHandle project_dockwidget_visibility_state_;
	Core::StateBoolHandle toolmanager_dockwidget_visibility_state_;
	Core::StateBoolHandle layermanager_dockwidget_visibility_state_;
	Core::StateBoolHandle measurement_project_dockwidget_visibility_state_;
	Core::StateBoolHandle history_dockwidget_visibility_state_;
	
	// Other widget visibilty state
	Core::StateBoolHandle preferences_manager_visibility_state_;
	Core::StateBoolHandle controller_visibility_state_;
	Core::StateBoolHandle message_window_visibility_state_;

	// -- Signals --
public:
	typedef boost::signals2::signal< void( std::string ) > window_signal_type;

	// OPEN_WINDOW_SIGNAL:
	// This signal is triggered after a window needs to be opened
	window_signal_type show_window_signal_;

	// CLOSE_WINDOW_SIGNAL:
	// This signal is triggered after a window needs to be closed
	window_signal_type close_window_signal_;

	// -- Access to windowid_list_ --
public:
	typedef std::set< std::string > windowid_list_type;

	// ADD_WINDOWID:
	// Mark a windowid as available
	void add_windowid( const std::string& windowid ); // << THREAD-SAFE

	// IS_WINDOWID:
	// Check whether window id is valid
	bool is_windowid( const std::string& windowid ); // << THREAD-SAFE
	
private:
	// INITIALIZE_STATES:
	// This function is called by the constructor to initialize the state variables
	void initialize_states();

private:
	boost::mutex windowid_list_mutex_;
	windowid_list_type windowid_list_;

};

} // namespace Seg3D

#endif
