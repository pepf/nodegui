import { NodeWidget } from '../QtWidgets/QWidget';
import addon from '../utils/addon';
import { NativeElement } from '../core/Component';

export class QMetaObject {
    native: NativeElement;
    constructor(qObject: NodeWidget) {
        this.native = new addon.QMetaObject(qObject.native);
    }
    className(): string {
        return this.native.className();
    }
    methodCount(): number {
        return this.native.methodCount();
    }
}
