﻿

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "PivotPage.xaml.h"




void ::geolocator::PivotPage::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///PivotPage.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///PivotPage.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the Pivot named 'pivot'
    pivot = safe_cast<::Windows::UI::Xaml::Controls::Pivot^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"pivot"));
    // Get the MapControl named 'MyMap'
    MyMap = safe_cast<::Windows::UI::Xaml::Controls::Maps::MapControl^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"MyMap"));
    // Get the TextBlock named 'labelCoords'
    labelCoords = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"labelCoords"));
    // Get the Button named 'buttonLaunch'
    buttonLaunch = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"buttonLaunch"));
    // Get the Button named 'buttonStop'
    buttonStop = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"buttonStop"));
    // Get the AppBarButton named 'AddAppBarButton'
    AddAppBarButton = safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"AddAppBarButton"));
    // Get the AppBarButton named 'SecondaryButton1'
    SecondaryButton1 = safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"SecondaryButton1"));
    // Get the AppBarButton named 'SecondaryButton2'
    SecondaryButton2 = safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"SecondaryButton2"));
}

void ::geolocator::PivotPage::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ButtonBase^>(target))->Click +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::geolocator::PivotPage::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&PivotPage::buttonLaunch_Click);
        break;
    case 2:
        (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ButtonBase^>(target))->Click +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::geolocator::PivotPage::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&PivotPage::buttonStop_Click);
        break;
    case 3:
        (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ButtonBase^>(target))->Click +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::geolocator::PivotPage::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&PivotPage::AddAppBarButton_Click);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

