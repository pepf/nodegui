import { Component } from "./Component";

export class AppRegistry {
  static components = new Set<Component>();
  static registerComponent(component: Component) {
    AppRegistry.components.add(component);
  }
  static removeComponent(component: Component) {
    AppRegistry.components.delete(component);
  }
  static removeAll() {
    AppRegistry.components.clear();
  }
}
