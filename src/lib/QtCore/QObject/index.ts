import { EventWidget } from "../../core/EventWidget";
import { QMetaObject } from "../QMetaObject";

export abstract class QObject extends EventWidget {
  inherits(className: string) {
    return this.native.inherits(className);
  }
  metaObject(): QMetaObject {
    return this.native.metaObject();
  }
}
