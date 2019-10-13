import { QLabel } from './lib/QtWidgets/QLabel';

function main() {
    const label = new QLabel();
    label.invoke('show');
    label.invoke('setText', 'hell12312o');
    (global as any).label = label;
}

main();
