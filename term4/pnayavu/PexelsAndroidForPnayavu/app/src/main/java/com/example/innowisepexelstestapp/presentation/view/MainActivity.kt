package com.example.innowisepexelstestapp.presentation.view

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import by.kirich1409.viewbindingdelegate.viewBinding
import com.example.innowisepexelstestapp.App
import com.example.innowisepexelstestapp.R
import com.example.innowisepexelstestapp.databinding.ActivityMainBinding
import com.example.innowisepexelstestapp.di.injectViewModel
import com.example.innowisepexelstestapp.presentation.navigation.Screens
import com.example.innowisepexelstestapp.presentation.viewmodel.MainViewModel
import com.github.terrakok.cicerone.Command
import com.github.terrakok.cicerone.Navigator
import com.github.terrakok.cicerone.NavigatorHolder
import com.github.terrakok.cicerone.Replace
import com.github.terrakok.cicerone.androidx.AppNavigator
import javax.inject.Inject

//todo закинуть библы в каталоги
//todo поменять serialize в bundle на parcel
//todo покрыть юнит-тестами какую-нить view-model
//todo сделать свайпы влево и вправо на фото в списке
//todo сделать экран множественного открытия с compose
//todo extended fab
//todo перевести picasso на glide
//todo исправить ошибку вылета при подключении интернета и попытке прогрузить staggeredMAnager
//todo отъебывается программа при notifyItemRangeInserted(photoPexelsArray.size - listSize, listSize). исправить
//todo закинуть нормально в viewmodel то, что при нажатии категории

//todo мб добавить кеширование на час
//todo мб поменять splashscreen на возможности сторонних библиотек
//todo мб добавить эффект нажатия на изображение
//todo мб добавить размер фото на кнопку скачивания
//todo БОЛЬШЕ USECASE
//todo You have several modules, but something is missing, could you find please what actually
//todo Imagine what could be cost doing like this in code, and how to prevent or wrap it?


class MainActivity : AppCompatActivity() {

    private val mViewBinding by viewBinding(ActivityMainBinding::bind)
    private val mViewModel: MainViewModel by injectViewModel()

    @Inject
    lateinit var mNavigatorHolder: NavigatorHolder

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        App.instance.appComponent.inject(this)
        setContentView(R.layout.activity_main)

        getSystemService(DOWNLOAD_SERVICE)

        if (savedInstanceState == null) {
            navigator.applyCommands(arrayOf<Command>(Replace(Screens.homeFragment())))
        }

        mViewModel.startSplashScreenAnim()
        mViewModel.delayedHideSplashScreen()
        setupObservers()
    }

    private val navigator: Navigator = object : AppNavigator(this, R.id.container) {
        override fun applyCommands(commands: Array<out Command>) {
            super.applyCommands(commands)
            supportFragmentManager.executePendingTransactions()
        }
    }

    override fun onResumeFragments() {
        super.onResumeFragments()
        mNavigatorHolder.setNavigator(navigator)
    }

    override fun onPause() {
        mNavigatorHolder.removeNavigator()
        super.onPause()
    }

    private fun setupObservers() = with(mViewBinding) {
        mViewModel.ldLogoVisibility.observe(this@MainActivity) {
            logo.visibility = it
        }
        mViewModel.ldLogoBackgroundVisibility.observe(this@MainActivity) {
            logoBackground.visibility = it
        }
        mViewModel.ldLogoStartAnim.observe(this@MainActivity) {
            logo.startAnimation(it)
        }
    }

}