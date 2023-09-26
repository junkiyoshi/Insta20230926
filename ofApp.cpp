#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetLineWidth(1.5);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 2;
	float theta_deg_step = 2;

	float radius = 230;
	float noise_threshold = 0.2;

	ofColor face_color = ofColor(255);
	ofColor line_color = ofColor(0);

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg <= 180; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(
				radius * cos(phi_deg * DEG_TO_RAD) * 0.01,
				radius * sin(phi_deg * DEG_TO_RAD) * 0.01,
				radius * cos(theta_deg * DEG_TO_RAD) * 0.01 +
				ofGetFrameNum() * 0.04);

			if (noise_value < noise_threshold) {

				this->line.addVertex(glm::vec3());
				this->line.addVertex(glm::vec3(
					radius * 2 * sin(theta_deg * DEG_TO_RAD) * cos(phi_deg * DEG_TO_RAD),
					radius * 2 * sin(theta_deg * DEG_TO_RAD) * sin(phi_deg * DEG_TO_RAD),
					radius * 2 * cos(theta_deg * DEG_TO_RAD)));

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);

				this->line.addColor(ofColor(0, 128, 255));
				this->line.addColor(ofColor(0, 128, 255, 0));

				continue;
			}

			auto noise_value_1 = ofNoise(
				radius * cos(phi_deg * DEG_TO_RAD) * 0.01,
				radius * sin(phi_deg * DEG_TO_RAD) * 0.01,
				radius * cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * 0.01 +
				ofGetFrameNum() * 0.04);
			auto noise_value_2 = ofNoise(
				radius * cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * 0.01,
				radius * sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * 0.01,
				radius * cos(theta_deg * DEG_TO_RAD) * 0.01 +
				ofGetFrameNum() * 0.04);
			auto noise_value_3 = ofNoise(
				radius * cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * 0.01,
				radius * sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * 0.01,
				radius * cos(theta_deg * DEG_TO_RAD) * 0.01 +
				ofGetFrameNum() * 0.04);
			auto noise_value_4 = ofNoise(
				radius * cos(phi_deg * DEG_TO_RAD) * 0.01,
				radius * sin(phi_deg * DEG_TO_RAD) * 0.01,
				radius * cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * 0.01 +
				ofGetFrameNum() * 0.04);

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

			this->face.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			if (noise_value_1 < noise_threshold) {

				this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				this->line.addColor(line_color); this->line.addColor(line_color);
			}

			if (noise_value_2 < noise_threshold) {

				this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				this->line.addColor(line_color); this->line.addColor(line_color);
			}

			if (noise_value_3 < noise_threshold) {

				this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				this->line.addColor(line_color); this->line.addColor(line_color);
			}

			if (noise_value_4 < noise_threshold) {

				this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				this->line.addColor(line_color); this->line.addColor(line_color);
			}

			for (int i = 0; i < vertices.size(); i++) {

				this->face.addColor(face_color);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(ofGetFrameNum());

	this->face.draw();
	this->line.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}