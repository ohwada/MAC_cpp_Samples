#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

#include "vmime/vmime.hpp"

// prototype
vmime::string getFolderPathString(vmime::shared_ptr <vmime::net::folder> f) ;
void addMessage(vmime::shared_ptr <vmime::net::folder> f);
void copyMessage(vmime::shared_ptr <vmime::net::folder> f,
	vmime::shared_ptr <vmime::net::message> msg);
vmime::shared_ptr <vmime::net::folder> changeFolder(vmime::shared_ptr <vmime::net::store> st );
void printFolders(vmime::shared_ptr <vmime::net::folder> folder, const int level = 0) ;
void showFlags(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg );
void	showEnvelope(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg);
void showHeader(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg);
void getFullHeaders(
vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg, std::string &headers);
void showStatus(vmime::shared_ptr <vmime::net::folder> f);
void showFolders( vmime::shared_ptr <vmime::net::store> st );
void showStructure(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> net_msg);


 /**
 *  getFolderPathString
 */
vmime::string getFolderPathString(vmime::shared_ptr <vmime::net::folder> f) 
{

	const vmime::string n = f->getName().getBuffer();

	if (n.empty()) {  // root folder

		return "/";

	} else {

		vmime::shared_ptr <vmime::net::folder> p = f->getParent();
		return getFolderPathString(p) + n + "/";
	}
}



/** Print folders and sub-folders on the standard output.
  *
  * @param folder current folder
  */
void printFolders(vmime::shared_ptr <vmime::net::folder> folder, const int level) 
{

	for (int j = 0 ; j < level * 2 ; ++j) {
		std::cout << " ";
	}

	const vmime::net::folderAttributes attr = folder->getAttributes();
	std::ostringstream attrStr;

	if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ALL) {
		attrStr << " \\use:All";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_ARCHIVE) {
		attrStr << " \\use:Archive";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_DRAFTS) {
		attrStr << " \\use:Drafts";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_FLAGGED) {
		attrStr << " \\use:Flagged";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_JUNK) {
		attrStr << " \\use:Junk";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_SENT) {
		attrStr << " \\use:Sent";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_TRASH) {
		attrStr << " \\use:Trash";
	} else if (attr.getSpecialUse() == vmime::net::folderAttributes::SPECIALUSE_IMPORTANT) {
		attrStr << " \\use:Important";
	}

	if (attr.getFlags() & vmime::net::folderAttributes::FLAG_HAS_CHILDREN) {
		attrStr << " \\flag:HasChildren";
	}
	if (attr.getFlags() & vmime::net::folderAttributes::FLAG_NO_OPEN) {
		attrStr << " \\flag:NoOpen";
	}

	for (size_t i = 0, n = attr.getUserFlags().size() ; i < n ; ++i) {
		attrStr << " \\" << attr.getUserFlags()[i];
	}

	std::cout << getFolderPathString(folder);
	std::cout << " " << attrStr.str();
	std::cout << std::endl;

	std::vector <vmime::shared_ptr <vmime::net::folder> > subFolders = folder->getFolders(false);

	for (unsigned int i = 0 ; i < subFolders.size() ; ++i) {
		printFolders(subFolders[i], level + 1);
	}
}



/** Print the MIME structure of a message on the standard output.
  *
  * @param s structure object
  * @param level current depth
  */
void printStructure(
	vmime::shared_ptr <const vmime::net::messageStructure> s,
	const int level=0 ) 
{

	for (size_t i = 0 ; i < s->getPartCount() ; ++i) {

		vmime::shared_ptr <const vmime::net::messagePart> part = s->getPartAt(i);

		for (int j = 0 ; j < level * 2 ; ++j) {
			std::cout << " ";
		} // for

		std::cout
			<< (part->getNumber() + 1) << ". "
			<< part->getType().generate()
			<< " [" << part->getSize() << " byte(s)]"
			<< std::endl;

		printStructure(part->getStructure(), level + 1);
	} // for

}




/**
 *  addMessage
  */
void addMessage(vmime::shared_ptr <vmime::net::folder> f)
{

        vmime::messageBuilder mb;

		mb.setExpeditor(vmime::mailbox("me@somewhere.com"));

		vmime::addressList to;
		to.appendAddress(vmime::make_shared <vmime::mailbox>("you@elsewhere.com"));
		mb.setRecipients(to);

		mb.setSubject(vmime::text("Test message from VMime"));
		mb.getTextPart()->setText(
		    vmime::make_shared <vmime::stringContentHandler>(
			"Body of test message from VMime"
			)
			);

        vmime::shared_ptr <vmime::message> msg = mb.construct();

		vmime::net::messageSet set = f->addMessage(msg);

		if (set.isEmpty()) {
                std::cout << "Message has successfully been added, "
				        << "but its UID/number is not known." << std::endl;
        } else {
                const vmime::net::messageRange& range = set.getRangeAt(0);

				if (set.isUIDSet()) {
                        const vmime::net::message::uid uid =
						dynamic_cast <const vmime::net::UIDMessageRange&>(range).getFirst();
                        std::cout << "Message has successfully been added, "
						    << "its UID is '" << uid << "'." << std::endl;
                } else {
                            const vmime::size_t number =
							dynamic_cast <const vmime::net::numberMessageRange&>(range).getFirst();
                            std::cout << "Message has successfully been added, "
							    << "its number is '" << number << "'." << std::endl;
				} // if (set.isUIDSet
		} //  		if (set.isEmpty()
}


/**
 *  copyMessage
  */
void copyMessage(vmime::shared_ptr <vmime::net::folder> f,
	vmime::shared_ptr <vmime::net::message> msg)
{

    vmime::net::messageSet set = f->copyMessages(f->getFullPath(),
		vmime::net::messageSet::byNumber(msg->getNumber()));

		if (set.isEmpty()) {
				std::cout << "Message has successfully been copied, "
						          << "but its UID/number is not known." << std::endl;

		} else {
						const vmime::net::messageRange& range = set.getRangeAt(0);

					if (set.isUIDSet()) {

							const vmime::net::message::uid uid =
								dynamic_cast <const vmime::net::UIDMessageRange&>(range).getFirst();

							std::cout << "Message has successfully been copied, "
							          << "its UID is '" << uid << "'." << std::endl;

					} else {

							const vmime::size_t number =
								dynamic_cast <const vmime::net::numberMessageRange&>(range).getFirst();

							std::cout << "Message has successfully been copied, "
							          << "its number is '" << number << "'." << std::endl;
					}
    }
}



/**
 *  changeFolder
  */
vmime::shared_ptr <vmime::net::folder> changeFolder(vmime::shared_ptr <vmime::net::store> st )
{

    std::cout << "Enter folder path (eg. /root/subfolder):" << std::endl;
	std::cout.flush();

	std::string path;
	std::getline(std::cin, path);

	vmime::shared_ptr <vmime::net::folder> newFolder = st->getRootFolder();

		for (std::string::size_type s = 0, p = 0 ; ; s = p + 1) {
						p = path.find_first_of('/', s);
						const std::string x = (p == std::string::npos)
							? std::string(path.begin() + s, path.end())
							: std::string(path.begin() + s, path.begin() + p);

						if (!x.empty()) {
							newFolder = newFolder->getFolder(vmime::utility::path::component(x));
						}

						if (p == std::string::npos) {
							break;
						}
    } // for

	    newFolder->open(vmime::net::folder::MODE_READ_WRITE);

		vmime::size_t count = newFolder->getMessageCount();

		std::cout << std::endl;
		std::cout << count << " message(s) in this folder" << std::endl;
	
    return newFolder;
}



/**
 *  showFlags
 */
void showFlags(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg )
{
    std::cout << "show message flags" << std::endl;
 
    f->fetchMessage(msg, vmime::net::fetchAttributes::FLAGS);

    int flags = msg->getFlags();
	if (flags & vmime::net::message::FLAG_SEEN) {
					std::cout << "FLAG_SEEN" << std::endl;
	}
	
    if (flags & vmime::net::message::FLAG_RECENT) {
					std::cout << "FLAG_RECENT" << std::endl;
	}
					
    if (flags & vmime::net::message::FLAG_REPLIED) {
				std::cout << "FLAG_REPLIED" << std::endl;
	}

	if (flags & vmime::net::message::FLAG_DELETED) {
				std::cout << "FLAG_DELETED" << std::endl;
	}

    if (flags & vmime::net::message::FLAG_MARKED) {
				std::cout << "FLAG_MARKED" << std::endl;
    }

    if (flags & vmime::net::message::FLAG_PASSED) {
				std::cout << "FLAG_PASSED" << std::endl;
	}

}


/**
 *  showEnvelope
  */
void	showEnvelope(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg)
{
    std::cout << "Show message envelope" << std::endl;

	vmime::net::fetchAttributes attr(vmime::net::fetchAttributes::ENVELOPE);

	// If you also want to fetch "Received: " fields:
	//attr.add("Received");

	f->fetchMessage(msg, attr);

		std::cout << std::endl;
	std::cout << msg->getHeader()->generate() << std::endl;
	std::cout << "----------"<< std::endl;

}


/**
 *  showHeader
  */
void showHeader(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg)
{
    std::cout << "Show message header" << std::endl;

    std::string headers;
    getFullHeaders( f, msg, headers);

	std::cout << std::endl;
	std::cout << headers << std::endl;
	std::cout << "----------" << std::endl;

}


/**
 *  getFullHeaders
  */
void getFullHeaders(
vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg, std::string &headers)
{

        f->fetchMessage(msg, vmime::net::fetchAttributes::FULL_HEADER);

		headers = msg->getHeader()->generate();

}



/**
 *  showStatus
 */
void showStatus(vmime::shared_ptr <vmime::net::folder> f)
{

    std::cout << "show status" << std::endl;

    vmime::size_t count, unseen;
	f->status(count, unseen);

    std::cout << count << " message(s)" << std::endl;
    std::cout << unseen << " unseen(s)" << std::endl;

}



 /**
 *  showFolders
 */
void showFolders( vmime::shared_ptr <vmime::net::store> st )
{

    std::cout << "show folders" << std::endl;

    vmime::shared_ptr <vmime::net::folder> root = st->getRootFolder();
    printFolders(root);
}



/**
 *  showStructure
  */
void showStructure(vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> net_msg)
{

        f->fetchMessage(net_msg, vmime::net::fetchAttributes::STRUCTURE);
		printStructure( net_msg->getStructure() );
}
