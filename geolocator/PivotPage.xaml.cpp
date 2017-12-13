//
// PivotPage.xaml.cpp
// Implémentation de la classe PivotPage.
//

#include "pch.h"
#include "PivotPage.xaml.h"
#include "ItemPage.xaml.h"
#include <thread>
#include <mutex>
#include <ctime>

using namespace std;
using namespace geolocator;
using namespace geolocator::Common;
using namespace geolocator::Data;
using namespace Windows::Devices::Geolocation;

using namespace concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// Pour plus d'informations sur le modèle Application Pivot, consultez la page http://go.microsoft.com/fwlink/?LinkID=391641

double duration;
String^ strCoords = "undefined";
mutex *_mutexGps;
mutex *_mutexChrono;
bool threadChronoIsRunning, threadGpsIsRunning, isOnTickDefined=false;

PivotPage::PivotPage()
{
	InitializeComponent();

	NavigationCacheMode = Navigation::NavigationCacheMode::Required;

	_resourceLoader = ResourceLoader::GetForCurrentView(L"Resources");

	auto navigationHelper = ref new Common::NavigationHelper(this);
	navigationHelper->LoadState += ref new LoadStateEventHandler(this, &PivotPage::NavigationHelper_LoadState);
	navigationHelper->SaveState += ref new SaveStateEventHandler(this, &PivotPage::NavigationHelper_SaveState);

	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));
	SetValue(_navigationHelperProperty, navigationHelper);

	_mutexChrono = new mutex();
	_mutexGps = new mutex();
}

DependencyProperty^ PivotPage::_navigationHelperProperty = nullptr;
DependencyProperty^ PivotPage::_defaultViewModelProperty = nullptr;

void PivotPage::RegisterDependencyProperties()
{
	if (_navigationHelperProperty == nullptr)
	{
		_navigationHelperProperty = DependencyProperty::Register("NavigationHelper",
			TypeName(Common::NavigationHelper::typeid), TypeName(PivotPage::typeid), nullptr);
	}

	if (_defaultViewModelProperty == nullptr)
	{
		_defaultViewModelProperty =
			DependencyProperty::Register("DefaultViewModel",
			TypeName(IObservableMap<String^, Object^>::typeid), TypeName(PivotPage::typeid), nullptr);
	}
}


IObservableMap<String^, Object^>^ PivotPage::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

NavigationHelper^ PivotPage::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

void PivotPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedTo(e);
}

void PivotPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

/// <summary>
/// Remplit la page à l'aide du contenu passé lors de la navigation. Tout état enregistré est également
/// fourni lorsqu'une page est recréée à partir d'une session antérieure.
/// </summary>
/// <param name="sender">
/// La source de l'événement, en général <see cref="NavigationHelper"/>.
/// </param>
/// <param name="e">Données d'événement qui fournissent le paramètre de navigation transmis à
/// <see cref="Frame->Navigate(Type, Object)"/> lors de la requête initiale de cette page et
/// un dictionnaire d'état conservé par cette page durant une session
/// antérieure. L'état n'aura pas la valeur Null lors de la première visite de la page.</param>
void PivotPage::NavigationHelper_LoadState(Object^ sender, LoadStateEventArgs^ e)
{
	(void) sender;	// Paramètre non utilisé
	(void) e;		// Paramètre non utilisé

	SampleDataSource::GetGroup(L"Group-1").then([this](SampleDataGroup^ sampleDataGroup)
	{
		DefaultViewModel->Insert(GetFirstGroupName(), sampleDataGroup);
	}, task_continuation_context::use_current());
}

/// <summary>
/// Conserve l'état associé à cette page en cas de suspension de l'application ou de
/// suppression de la page du cache de navigation. Les valeurs doivent être conforme aux
/// exigences en matière de sérialisation de <see cref="SuspensionManager.SessionState"/>.
/// </summary>
/// <param name="sender">
/// La source de l'événement, en général <see cref="NavigationHelper"/>.
/// </param>
/// <param name="e">
/// Données d'événement qui fournissent un dictionnaire vide à remplir avec un état sérialisable.
/// </param>
void PivotPage::NavigationHelper_SaveState(Object^ sender, SaveStateEventArgs^ e)
{
	// TODO: enregistrer l'état unique de la page ici.
}

/// <summary>
/// Charge le contenu pour le second élément Pivot lorsqu'il devient visible.
/// </summary>
void PivotPage::SecondPivot_Loaded(Object^ sender, RoutedEventArgs ^e)
{
	(void) sender;	// Paramètre non utilisé
	(void) e;		// Paramètre non utilisé

	// TODO: créer un modèle de données approprié pour le domaine posant problème afin de remplacer les exemples de données.
	SampleDataSource::GetGroup(L"Group-2").then([this](SampleDataGroup^ sampleDataGroup)
	{
		DefaultViewModel->Insert(GetSecondGroupName(), sampleDataGroup);
	}, task_continuation_context::use_current());
}

/// <summary>
/// Ajoute un élément à la liste en cas de clic sur le bouton de la barre de l'application.
/// </summary>
void PivotPage::AddAppBarButton_Click(Object^ sender, RoutedEventArgs ^e)
{
	String^ groupName;
	if (pivot->SelectedIndex == 0)
	{
		groupName = GetFirstGroupName();
	}
	else
	{
		groupName = GetSecondGroupName();
	}

	auto group = safe_cast<SampleDataGroup^>(DefaultViewModel->Lookup(groupName));
	auto nextItemId = group->Items->Size + 1;
	std::wstring uniqueId = std::wstring(L"Group-") + std::to_wstring(pivot->SelectedIndex + 1) + std::wstring(L"-Item-") + std::to_wstring(nextItemId);
	std::wstring title = std::wstring(L"Item Title: ") + std::to_wstring(nextItemId);

	auto newItem = ref new SampleDataItem(
		ref new String(uniqueId.c_str()),
		ref new String(title.c_str()),
		nullptr,
		nullptr,
		_resourceLoader->GetString("NewItemDescription"),
		nullptr);

	group->Items->Append(newItem);

	// Faire apparaître le nouvel élément.
	auto container = safe_cast<ContentControl^>(pivot->ContainerFromIndex(pivot->SelectedIndex));
	auto listView = safe_cast<ListView^>(container->ContentTemplateRoot);
	listView->ScrollIntoView(newItem, ScrollIntoViewAlignment::Leading);
}

/// <summary>
/// Appelé lorsqu'un utilisateur clique sur un élément appartenant à une section.
/// </summary>
void PivotPage::ItemView_ItemClick(Object^ sender, ItemClickEventArgs ^e)
{
	auto itemId = safe_cast<SampleDataItem^>(e->ClickedItem)->UniqueId;
	if (!Frame->Navigate(ItemPage::typeid, itemId))
	{
		throw ref new FailureException(_resourceLoader->GetString(L"NavigationFailedExceptionMessage"));
	}
}

void geolocator::PivotPage::OnTick(Object^ sender, Object^ e) {
	_mutexChrono->unlock();
	_mutexGps->unlock();
	_mutexChrono->lock();
	_mutexGps->lock();
	labelCoords->Text = duration + " : " + strCoords;
}

void ThreadGPS() {
	Geolocator^ geolocator = ref new Geolocator();
	geolocator->ReportInterval = 250;
	geolocator->DesiredAccuracyInMeters = (unsigned int)5;
	threadGpsIsRunning = true;
	while (threadGpsIsRunning) {
		_mutexGps->lock();
		auto m_getOperation = geolocator->GetGeopositionAsync();

		m_getOperation->Completed = ref new AsyncOperationCompletedHandler<Geoposition^>(
			[=](IAsyncOperation<Geoposition^>^ asyncOperation, AsyncStatus status) mutable {
			if (status != AsyncStatus::Error) {
				Geoposition^ position = asyncOperation->GetResults();
				strCoords = position->Coordinate->Latitude + ";" + position->Coordinate->Longitude;
			}
			else {
				strCoords = "Erreur";
			}
		});

		_mutexGps->unlock();
		Sleep(1000);
	}
}

void ThreadChrono() {
	std::clock_t start;
	start = std::clock();
	threadChronoIsRunning = true;
	while (threadChronoIsRunning) {
		_mutexChrono->lock();
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		_mutexChrono->unlock();
		Sleep(500);
	}
}

void geolocator::PivotPage::buttonLaunch_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	buttonLaunch->IsEnabled = false;
	buttonStop->IsEnabled = true;

	_mutexChrono->lock();
	_mutexGps->lock();

	if (!isOnTickDefined) {
		timer = ref new DispatcherTimer();
		TimeSpan span;
		span.Duration = 500;
		timer->Interval = span;
		auto reigstrationToken = timer->Tick += ref new EventHandler<Object^>(this, &PivotPage::OnTick);
		isOnTickDefined = true;
	}

	timer->Start();
	
	_threadGps = new thread(ThreadGPS);
	_threadChrono = new thread(ThreadChrono);
}


void geolocator::PivotPage::buttonStop_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	buttonLaunch->IsEnabled = true;
	buttonStop->IsEnabled = false;

	threadChronoIsRunning = false;
	threadGpsIsRunning = false;

	_threadChrono->join();
	_threadGps->join();

	timer->Stop();

	_mutexChrono->unlock();
	_mutexGps->unlock();
}


