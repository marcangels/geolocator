﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class Pivot;
                ref class TextBlock;
                ref class Button;
                ref class ListView;
            }
        }
    }
}
namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                namespace Maps {
                    ref class MapControl;
                }
            }
        }
    }
}

namespace geolocator
{
    partial ref class PivotPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::Pivot^ pivot;
        private: ::Windows::UI::Xaml::Controls::Maps::MapControl^ MyMap;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ labelCoords;
        private: ::Windows::UI::Xaml::Controls::Button^ buttonLaunch;
        private: ::Windows::UI::Xaml::Controls::Button^ buttonStop;
        private: ::Windows::UI::Xaml::Controls::ListView^ listView;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ labelStatus;
    };
}

