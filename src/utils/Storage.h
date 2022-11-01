#pragma once

#include "ForwardDeclare.h"
#include "utils/Memory.h"
#include <string>

namespace sol::utils
{
	class Storage
	{
	public:
		template<class R, class W>
		Storage() 
		{
			m_reader = sol_make_shared<R>();
			m_writer = sol_make_shared<W>();
		}
		
		StorageReaderSPtr reader() const noexcept { return m_reader; }
		StorageWriterSPtr writer() const noexcept { return m_writer; }

	private:
		StorageReaderSPtr m_reader;
		StorageWriterSPtr m_writer;
	};

	class StorageWriter
	{
	public:
		virtual ~StorageWriter() = default;

		virtual bool write(std::string_view raw) = 0;
	};

	class FileStorageWriter : public StorageWriter
	{
	public:
		virtual bool write(std::string_view raw) override;
	};

	class StorageReader
	{
	public:
		virtual ~StorageReader() = default;

		virtual std::string read() = 0;
	};

	class FileStorageReader : public StorageReader
	{
	public:
		virtual std::string read() override;
	};

} // namespace sol::auth
