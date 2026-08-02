# Cloud and Alexa End-to-End Architecture

Alexa directives are translated into expiring LYNQ remote commands. The cloud authorizes the household and target Hub, holds commands while the Hub is offline, and records acknowledgements. The Hub resolves the persistent device command through the same dispatch engine used by local controls, Scenes and automations, then routes execution to the assigned Node.

Production deployment still requires OAuth account linking, hosted HTTPS endpoints, persistent databases, secrets management, signed Hub sessions and Amazon certification.
