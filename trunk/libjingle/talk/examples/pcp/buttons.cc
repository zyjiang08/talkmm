//$Id: buttons.cc,v 1.2 2004/02/10 14:48:47 murrayc Exp $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "buttons.h"
#include <iostream>

Buttons::Buttons() 
{
  //m_button.add_pixlabel("info.xpm", "cool button");
   
  set_title("Pixmap'd buttons!");
  set_border_width(10);

  //m_button.signal_clicked().connect( sigc::mem_fun(*this, &Buttons::on_button_clicked) );
  
  //add(m_button);

  add(v_button);
  //v_button.set_sensitive(false);

  show_all_children();
}

Buttons::~Buttons()
{
}

void Buttons::on_button_clicked()
{
  std::cout << "The Button was clicked." << std::endl;
  int alpha=2;
  int x,y;
  this->get_window()->get_position(x,y);
  Glib::RefPtr<Gdk::Window> win=this->get_window();
  std::cout<<" Position x = "<<x<<" y = "<<y<<std::endl;
  for(int i=0; i<180;i++)
  {
	  if(i%2==0)
	  {
		  win->move(x+alpha,y);
		  win->show();
		  win->move(x, y+alpha);
		  win->show();
	  }
	  else
	  {
		  //win->move(x-(alpha),y);
		  win->move(x-(alpha*2),y);
		  win->show();
		  //win->move(x, y-(alpha));
		  win->move(x, y-(alpha*2));
		  win->show();
	  }
  }

	  win->move(x,y);
	  win->show();


}

