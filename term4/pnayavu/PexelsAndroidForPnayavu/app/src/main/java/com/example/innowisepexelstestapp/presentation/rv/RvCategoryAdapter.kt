package com.example.innowisepexelstestapp.presentation.rv

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.recyclerview.widget.RecyclerView
import com.example.innowisepexelstestapp.App
import com.example.innowisepexelstestapp.R
import com.example.innowisepexelstestapp.databinding.RvCategoryItemBinding
import com.example.innowisepexelstestapp.model.Category
import com.example.innowisepexelstestapp.util.ResourceProvider
import javax.inject.Inject

class RvCategoryAdapter(private val mListener: ClickListener) :
    RecyclerView.Adapter<RvCategoryAdapter.CategoryHolder>() {

    val categories = mutableListOf<Category>()

    class CategoryHolder(view: View) : RecyclerView.ViewHolder(view) {

        @Inject
        lateinit var resourceProvider: ResourceProvider
        private val binding = RvCategoryItemBinding.bind(view)
        init {
            App.instance.appComponent.inject(this)
        }


        fun bind(category: Category, position: Int, listener: ClickListener) = with(binding) {
            btn.text = category.name

            if(category.isActive) {
                btn.backgroundTintList = resourceProvider.getAttrColor(
                    com.google.android.material.R.attr.colorTertiary, btn.context
                )
                btn.typeface = resourceProvider.getFont(R.font.mulish_700)
            } else {
                btn.backgroundTintList = resourceProvider.getAttrColor(
                    com.google.android.material.R.attr.colorSurfaceContainer, btn.context
                )
                btn.typeface = resourceProvider.getFont(R.font.mulish_400)
            }
            itemView.setOnClickListener {
                listener.onClickCategory(category, position)
            }
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CategoryHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.rv_category_item, parent, false)
        return CategoryHolder(view)
    }

    override fun onBindViewHolder(holder: CategoryHolder, position: Int) {
        holder.bind(categories[position], position, mListener)
    }

    override fun getItemCount(): Int {
        return categories.size
    }

    fun addCategories(categoriesToAdd: List<Category>) {
        categories.clear() //todo тут добавить не через задницу
        categories.addAll(categoriesToAdd)
        notifyDataSetChanged()
    }

    interface ClickListener {
        fun onClickCategory(category: Category, position: Int)
    }
}