//
// Created by veyrie_f on 5/11/16.
//

#ifndef CPP_INDIE_STUDIO_ISELECTIONBOX_HPP
#define CPP_INDIE_STUDIO_ISELECTIONBOX_HPP

/*
 * \brief Class representing a box where a user can select things
 */
class ISelectionBox
{
public:
    ISelectionBox()
    {}
    virtual ~ISelectionBox()
    {}

public:
    virtual void Update() = 0;
    virtual void SelectNext() = 0;
    virtual void SelectPrev() = 0;
    virtual void OnSelect() = 0;
};

#endif //CPP_INDIE_STUDIO_ISELECTIONBOX_HPP
