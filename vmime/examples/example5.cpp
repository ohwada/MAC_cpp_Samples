// https://github.com/kisli/vmime/blob/master/examples/example5.cpp

//
// VMime library (http://www.vmime.org)
// Copyright (C) 2002 Vincent Richard <vincent@vmime.org>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// Linking this library statically or dynamically with other modules is making
// a combined work based on this library.  Thus, the terms and conditions of
// the GNU General Public License cover the whole combination.
//

//
// EXAMPLE DESCRIPTION:
// ====================
// This sample program demonstrate the use of the messageParser component
// to enumerate the attachments in a message.
//
// For more information, please visit:
// http://www.vmime.org/
//

#include <iostream>
#include <locale>
#include <clocale>

#include "vmime/vmime.hpp"
#include "vmime/platforms/posix/posixHandler.hpp"


int main() {

	std::cout << std::endl;

	// Set the global C and C++ locale to the user-configured locale.
	// The locale should use UTF-8 encoding for these tests to run successfully.
	try {
		std::locale::global(std::locale(""));
	} catch (std::exception &) {
		std::setlocale(LC_ALL, "");
	}

	try {

		vmime::messageParser mp("<...MIME message content...>");

		// Enumerate attachments
		for (size_t i = 0 ; i < mp.getAttachmentCount() ; ++i) {

			const vmime::attachment& att = *mp.getAttachmentAt(i);

			// Media type (content type) is in "att.getType()"
			// Name is in "att.getName()"
			// Description is in "att.getDescription()"
			// Data is in "att.getData()"
		}

	// VMime exception
	} catch (vmime::exception& e) {

		std::cout << "vmime::exception: " << e.what() << std::endl;
		throw;

	// Standard exception
	} catch (std::exception& e) {

		std::cout << "std::exception: " << e.what() << std::endl;
		throw;
	}

	std::cout << std::endl;

	return 0;
}
