#pragma once

#include <cryptosqlite/cryptosqlite.h>
#include "../sqlite_modern_cpp.h"

namespace sqlite {
	struct cryptosqlite_config : public sqlite_config {
		std::string key;
	};

	class cryptosqlite_database : public database {
	public:
		cryptosqlite_database(const std::string &db_name, const cryptosqlite_config &config):
				database(db_name, prepare_config(config)) {

			if(auto ret = sqlite3_key(_db.get(), config.key.data(), config.key.size()))
				errors::throw_sqlite_error(ret);
		}

		// TODO: add utf16 support

	private:
		// workaround preparing the sqlite3_open before the base constructor calls it
		const cryptosqlite_config &prepare_config(const cryptosqlite_config &config) {
			sqlite3_prepare_open_encrypted(config.key.data(), config.key.size());
			return config;
		}

	};
}
