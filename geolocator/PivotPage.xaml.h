﻿//
// PivotPage.xaml.h
// Déclaration de la classe PivotPage.
//

#pragma once

#include "PivotPage.g.h"
#include <thread>
#include <mutex>

namespace geolocator
{
	public ref class PivotPage sealed
	{
		Platform::String^ GetFirstGroupName() const
		{
			return ref new Platform::String(L"FirstGroup");
		}

		Platform::String^ GetSecondGroupName() const
		{
			return ref new Platform::String(L"SecondGroup");
		}

	public:
		PivotPage();

		static void RegisterDependencyProperties();
		static property Windows::UI::Xaml::DependencyProperty^ DefaultViewModelProperty
		{
			Windows::UI::Xaml::DependencyProperty^ get() { return _defaultViewModelProperty; }
		}

		static property Windows::UI::Xaml::DependencyProperty^ NavigationHelperProperty
		{
			Windows::UI::Xaml::DependencyProperty^ get() { return _navigationHelperProperty; }
		}

		/// <summary>
		/// Obtient le <see cref="NavigationHelper"/> associé à ce <see cref="Page"/>.
		/// </summary>
		property Common::NavigationHelper^ NavigationHelper
		{
			Common::NavigationHelper^ get();
		}

		/// <summary>
		/// Obtient le modèle d'affichage pour ce <see cref="Page"/>.
		/// Cela peut être remplacé par un modèle d'affichage fortement typé.
		/// </summary>
		property Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^ DefaultViewModel
		{
			Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^  get();
		}

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		~PivotPage();
		std::thread *_threadGps;
		std::thread *_threadChrono;
		Windows::UI::Xaml::DispatcherTimer^ timer;
		Windows::Devices::Geolocation::Geolocator^ geolocator;

		Windows::ApplicationModel::Resources::ResourceLoader^ _resourceLoader;

		void SecondPivot_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void NavigationHelper_LoadState(Platform::Object^ sender, Common::LoadStateEventArgs^ e);
		void NavigationHelper_SaveState(Platform::Object^ sender, Common::SaveStateEventArgs^ e);

		static Windows::UI::Xaml::DependencyProperty^ _defaultViewModelProperty;
		static Windows::UI::Xaml::DependencyProperty^ _navigationHelperProperty;
		void buttonLaunch_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void buttonStop_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnTick(Platform::Object^ sender, Object^ e);
	};
}
