/*
 * Copyright (c) 2014 Mark Liversedge (liversedge@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Specification.h"
#include "RideItem.h"

Specification::Specification(DateRange dr, FilterSet fs) : dr(dr), fs(fs) {}
Specification::Specification() {}

// does the rideitem pass the specification ?
bool 
Specification::pass(RideItem*item)
{
    return (dr.pass(item->dateTime.date()) && fs.pass(item->fileName));
}

// set criteria
void 
Specification::setDateRange(DateRange dr)
{
    this->dr = dr;
}

void 
Specification::setFilterSet(FilterSet fs)
{
    this->fs = fs;
}
