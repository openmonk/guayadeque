// -------------------------------------------------------------------------------- //
//	Copyright (C) 2008-2010 J.Rios
//	anonbeat@gmail.com
//
//    This Program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2, or (at your option)
//    any later version.
//
//    This Program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; see the file LICENSE.  If not, write to
//    the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//    http://www.gnu.org/copyleft/gpl.html
//
// -------------------------------------------------------------------------------- //
#ifndef TRANSCODE_H
#define TRANSCODE_H

#include <wx/event.h>
#include <wx/wx.h>

#include <gst/gst.h>

enum guTranscodeFormat {
    guTRANSCODE_FORMAT_KEEP,
    guTRANSCODE_FORMAT_MP3,
    guTRANSCODE_FORMAT_OGG,
    guTRANSCODE_FORMAT_FLAC,
    guTRANSCODE_FORMAT_AAC,
    guTRANSCODE_FORMAT_WMA
};

enum guPortableMediaTranscodeQuality {      // mp3  ogg flac aac wma
    guTRANSCODE_QUALITY_KEEP,
    guTRANSCODE_QUALITY_VERY_HIGH,          // 320  240
    guTRANSCODE_QUALITY_HIGH,               // 256  160
    guTRANSCODE_QUALITY_VERY_GOOD,          // 192  140
    guTRANSCODE_QUALITY_GOOD,               // 160  120
    guTRANSCODE_QUALITY_NORMAL,             // 128  110
    guTRANSCODE_QUALITY_LOW,                // 96   96
    guTRANSCODE_QUALITY_VERY_LOW            // 64   70
};


// -------------------------------------------------------------------------------- //
class guTranscodeThread : public wxThread
{
  protected :
    wxString        m_Source;
    wxString        m_Target;
    int             m_Format;
    int             m_Quality;
    bool            m_Running;
    GstElement *    m_Pipeline;

    void            BuildPipeline( void );
    bool            BuildEncoder( GstElement ** enc, GstElement ** mux );

  public :
    guTranscodeThread( const wxChar * source, const wxChar * target, const int format, const int quality );
    ~guTranscodeThread();

    virtual ExitCode    Entry();
    void                Stop( void );
    bool                IsTranscoding( void ) { return m_Running; }
    bool                IsOk( void ) { return ( m_Pipeline != NULL ); }

};

#endif
// -------------------------------------------------------------------------------- //
