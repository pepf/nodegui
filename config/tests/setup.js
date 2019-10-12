const { QApplication } = require('../../dist');
module.exports = function() {
    global.qApp = QApplication.instance();
    qApp.setQuitOnLastWindowClosed(false);
};
