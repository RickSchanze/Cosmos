/**
 * @file BaseUIElement.h
 * @author Echo
 * @Date 2023/11/13
 * @brief
 */

#ifndef BASEUIELEMENT_H
#define BASEUIELEMENT_H

class BaseUIElement {
public:
  virtual void Render() = 0;
  virtual ~BaseUIElement() = default;
};

#endif // BASEUIELEMENT_H
