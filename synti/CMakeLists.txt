#=============================================================================
#  OOMidi
#  OpenOctave Midi and Audio Editor
#  $Id:$
#
#  Copyright (C) 2002-2006 by Werner Schweer and others
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#=============================================================================

include_directories(
   .
   ${CMAKE_CURRENT_BINARY}
   ${PROJECT_SOURCE_DIR}
   ${PROJECT_SOURCE_DIR}/oom
   ${PROJECT_SOURCE_DIR}/oom/widgets
   ${PROJECT_SOURCE_DIR}/synti
   )

set (SubDirs
      libsynti
      )

if (ENABLE_EXPERIMENTAL)
      set (SubDirs ${SubDirs} s1 )
endif (ENABLE_EXPERIMENTAL)

if (HAVE_FLUIDSYNTH)
      set (SubDirs ${SubDirs} fluid fluidsynth )
endif (HAVE_FLUIDSYNTH)

subdirs(${SubDirs})


