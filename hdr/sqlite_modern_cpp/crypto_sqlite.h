#pragma once

#include <crypto_sqlite/crypto_sqlite.h>
#include "../sqlite_modern_cpp.h"

namespace sqlite {
	struct crypto_sqlite_config : public sqlite_config {
		std::string key;
	};

	class crypto_sqlite_database : public database {
	public:
		crypto_sqlite_database(const std::string &db_name, const crypto_sqlite_config &config):
				database(db_name, prepare_config(config)) {

			if(auto ret = sqlite3_key(_db.get(), config.key.data(), config.key.size()))
				errors::throw_sqlite_error(ret);
		}

		// TODO: add utf16 support

	private:
		// workaround preparing the sqlite3_open before the base constructor calls it
		const crypto_sqlite_config &prepare_config(const crypto_sqlite_config &config) {
			sqlite3_prepare_open_encrypted(config.key.data(), config.key.size());
			return config;
		}

	};
}
