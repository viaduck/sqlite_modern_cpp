#pragma once

#ifndef SQLITE_HAS_CODEC
#define SQLITE_HAS_CODEC
#endif

#include "../sqlite_modern_cpp.h"

namespace sqlite {
	struct cryptosqlite_config : public sqlite_config {
		std::string key;
	};

	class cryptosqlite_database : public database {
	public:
		cryptosqlite_database(std::string db, const cryptosqlite_config &config):
				database(db, prepare_config(db, config)) {

			if(auto ret = sqlite3_key(_db.get(), config.key.data(), config.key.size()))
				errors::throw_sqlite_error(ret);
		}

		// TODO: add utf16 support

	private:
		// workaround for decrypting the sqlite3 header before the base constructor calls sqlite3_open
		const cryptosqlite_config &prepare_config(const std::string &db, const cryptosqlite_config &config) {
			sqlite3_prepare_open_encrypted(db.c_str(), config.key.c_str(), config.key.size());
			return config;
		}

	};
}
