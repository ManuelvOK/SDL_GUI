#include <controllers/interface_controller.h>

#include <gui/drawable_tree_builder.h>
#include <util/xml_parser.h>

using namespace SDL_GUI;

InterfaceController::InterfaceController(const std::string template_file_path,
        InterfaceModel *interface_model, const InputModelBase *input_model)
    : _template_file_path(template_file_path), _interface_model(interface_model),
    _input_model(input_model) {
    this->init();
}

void InterfaceController::update() {
    Position current_position = this->_input_model->current_position();
    this->_interface_model->drawable_tree()->map([current_position](Drawable *drawable){
            drawable->recalculate();
            if (drawable->has_hover_style() && drawable->is_inside(current_position)) {
                drawable->set_current_style(&drawable->_hover_style);
            } else {
                drawable->set_current_style(&drawable->_default_style);
            }
        });
}

void InterfaceController::init() {
    /* parse template file */
    DrawableTreeBuilder builder(this->_interface_model->font());
    XmlParser<Drawable> parser(&builder);
    this->_interface_model->set_drawable_tree(parser.parse_file(this->_template_file_path));
}
