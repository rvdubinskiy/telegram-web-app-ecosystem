const dotenv = require('dotenv');
const path = require('path');

(function () {
  dotenv.config({ path: path.resolve(__dirname, `../../.env.local`) });
})();
