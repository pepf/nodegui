import { QLabel } from './lib/QtWidgets/QLabel';

function main() {
    const label = new QLabel();
    const meta = label.metaObject();
    console.log(meta.className(), meta.methodCount());
    (global as any).label = label;
}

main();
