// https://github.com/kisli/vmime/blob/master/examples/example1.cpp

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
// to build a simple message.
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
				"using the vmime::messageBuilder component."
			)
		);

		// Construction
		vmime::shared_ptr <vmime::message> msg = mb.construct();

		// Raw text generation
		std::cout << "Generated message:" << std::endl;
		std::cout << "==================" << std::endl;

		vmime::utility::outputStreamAdapter out(std::cout);
		msg->generate(out);

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


// Generated message:
// ==================
// Subject: My first message generated with vmime::messageBuilder
// From: me@somewhere.com
// To: you@elsewhere.com
// Bcc: you-bcc@nowhere.com
// Date: Sat, 26 Dec 2020 21:54:54 +0900
// Mime-Version: 1.0
// Content-Type: text/plain; charset=us-ascii
//Content-Transfer-Encoding: quoted-printable
//
// I'm writing this short text to test message construction using the vmime::messageBuilder component.


