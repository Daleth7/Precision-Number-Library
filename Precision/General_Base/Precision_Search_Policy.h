#ifndef PRECISION_IMAGE_SEARCH_POLICY_HHH___H___
#define PRECISION_IMAGE_SEARCH_POLICY_HHH___H___

namespace Precision{
    namespace Search_Policy{
        struct Normal{}; // Search by equality(==) and guarantee Theta(n/2) time
        struct Binary{}; // Search by range(<) and guarantee Theta(log(n)) time
    }
}

#endif