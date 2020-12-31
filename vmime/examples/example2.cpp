// g++ example2.cpp -std=c++11 `pkg-config --cflags --libs vmime` 

// TODO:
// get the following error
// vmime::exception: Error opening file.
// relative path don't work
// absolute path works well
// try smtp_attach.cpp


// https://github.com/kisli/vmime/blob/master/examples/example2.cpp

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
// This sample program demonstrate the use of the messageBuilder component
// to build a simple message with an attachment.
//
// For more information, please visit:
// http://www.vmime.org/
//

#include <iostream>
#include <locale>
#include <clocale>
#include "vmime/vmime.hpp"
#include "vmime/platforms/posix/posixHandler.hpp"


/**
 * main
 */
int main(void)
{

	std::cout << std::endl;

	// Set the global C and C++ locale to the user-configured locale.
	// The locale should use UTF-8 encoding for these tests to run successfully.
	try {
		std::locale::global(std::locale(""));
	} catch (std::exception &) {
		std::setlocale(LC_ALL, "");
	}

	try {

		vmime::messageBuilder mb;

		// Fill in the basic fields
		mb.setExpeditor(vmime::mailbox("me@somewhere.com"));

		vmime::addressList to;
		to.appendAddress(vmime::make_shared <vmime::mailbox>("you@elsewhere.com"));

		mb.setRecipients(to);

		vmime::addressList bcc;
		bcc.appendAddress(vmime::make_shared <vmime::mailbox>("you-bcc@nowhere.com"));

		mb.setBlindCopyRecipients(bcc);

		mb.setSubject(vmime::text("My first message generated with vmime::messageBuilder"));

		// Message body
		mb.getTextPart()->setText(
			vmime::make_shared <vmime::stringContentHandler>(
				"I'm writing this short text to test message construction " \
				"with attachment, using the vmime::messageBuilder component."
			)
		);

std::string file = __FILE__;
std::cout << "file: "<< file << std::endl;

		// Adding an attachment
		vmime::shared_ptr <vmime::fileAttachment> a =
			vmime::make_shared <vmime::fileAttachment>(
			//	__FILE__,                                       // full path to file
				file,                                       // full path to file
				vmime::mediaType("application/octet-stream"),   // content type
				vmime::text("My first attachment")              // description
			);

		a->getFileInfo().setFilename("example2.cpp");
		a->getFileInfo().setCreationDate(vmime::datetime("30 Apr 2003 14:30:00 +0200"));

		mb.attach(a);

		// Construction
		vmime::shared_ptr <vmime::message> msg = mb.construct();

		// Raw text generation
		vmime::string dataToSend = msg->generate();

		std::cout << "Generated message:" << std::endl;
		std::cout << "==================" << std::endl;
		std::cout << std::endl;
		std::cout << dataToSend << std::endl;

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


// vmime::exception: Error opening file.




